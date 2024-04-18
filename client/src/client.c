/*
** EPITECH PROJECT, 2024
** my_teams [WSL: Arch]
** File description:
** client
*/

#include "client.h"
#include "commands.h"
#include "debug_print.h"
#include "events.h"
#include "events_structures.h"
#include "logging_client.h"
#include "protocol.h"

#include <stdlib.h>
#include <sys/queue.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <stdint.h>
#include <stddef.h>
#include <signal.h>

static const bool *is_running = (const bool *)1;

static const char *HELP = "USAGE:"
"\t./myteams_cli ip port\n"
"DESCRIPTION:"
"\tip\tis the server ip address on which the server should connect\n"
"\tport\tis the port number on which the server should connect\n";

static void handle_sigint(int sig)
{
    (void)sig;
    fprintf(stdout, "Exiting...\n");
    is_running = false;
}

static char *get_client_input(void)
{
    static char input[8096];
    ssize_t bytes_read = 0;
    int flags = 0;

    flags = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);
    bytes_read = read(STDIN_FILENO, input, 8096 - 1);
    if (bytes_read == -1) {
        if (errno == EAGAIN || errno == EWOULDBLOCK)
            return NULL;
        perror("read");
        return NULL;
    } else if (bytes_read == 0)
        return NULL;
    input[bytes_read] = '\0';
    return input;
}

static void free_args(char **args)
{
    if (args) {
        for (int i = 0; args[i]; i++) {
            free(args[i]);
        }
        free(args);
        args = NULL;
    }
}

static bool format_args(char **args)
{
    for (int i = 1; args[i]; i++) {
        if (args[i][0] == '"' && args[i][strlen(args[i]) - 1] == '"') {
            memmove(args[i], args[i] + 1, strlen(args[i]));
            args[i][strlen(args[i]) - 1] = '\0';
        } else {
            fprintf(stdout, "Invalid argument: %s\n", args[i]);
            free_args(args);
            args = NULL;
            return false;
        }
    }
    return true;
}

static char **get_args_from_input(char *input)
{
    int space_count = 0;
    char **args = NULL;
    char *token = NULL;
    int i = 0;

    for (int j = 0; input[j]; j++)
        if (input[j] == ' ')
            space_count++;
    args = malloc(sizeof(char *) * (space_count + 2));
    token = strtok(input, " \n");
    for (; token; i++) {
        args[i] = strdup(token);
        token = strtok(NULL, " \n");
    }
    args[i] = NULL;
    return args;
}

static bool check_login(c_client_t *client)
{
    if (!client->user.uuid[0]) {
        fprintf(stdout, "You need to log in first\n");
        client_error_unauthorized();
        return false;
    }
    return true;
}

static void process_command(char *input, c_client_t *client, p_packet_t *p)
{
    char **args = NULL;
    char *command = NULL;

    if (!input)
        return;
    args = get_args_from_input(input);
    if (!args || !args[0]) {
        free_args(args);
        return;
    }
    if (!format_args(args))
        return;
    command = args[0];
    DEBUG_PRINT("Processing command: %s\n", command);
    for (int i = 0; commands[i].name; i++)
        if (!strcmp(commands[i].name, command) && commands[i].func
            && (!commands[i].need_login || check_login(client)))
            commands[i].func(args, (void *)client, p);
    free_args(args);
    return;
}

static void wait_for_logout(c_client_t *client)
{
    p_packet_t packet = {
        .type = INT16_MAX,
        .data = {0}
    };

    p_client_send_packet(
        client->p_client,
        EVT_DISCONNECT,
        client->user.uuid,
        UUID_LENGTH
    );
    while (!p_client_listen(client->p_client, &packet)
        && packet.type != EVT_DISCONNECT)
        client_logger(&packet, client);
}

static void start_cli(c_client_t *client)
{
    p_packet_t packet = {
        .type = INT16_MAX,
        .data = {0}
    };

    if (!client->p_client) {
        fprintf(stdout, "Failed to connect to server\n");
        return;
    }
    while (is_running) {
        signal(SIGINT, handle_sigint);
        p_client_listen(client->p_client, &packet);
        process_priority_queue(&client->queue, client);
        process_command(get_client_input(), client, &packet);
        add_to_priority_queue(&packet, &client->queue);
    }
    wait_for_logout(client);
}

int client(int ac, char **av)
{
    int isHelpRequested = ac > 1 && (!strcmp(av[1], "--help")
        || !strcmp(av[1], "-h"));
    c_client_t *client = malloc(sizeof(c_client_t));

    if (ac != 3 || isHelpRequested) {
        fprintf(isHelpRequested ? stdout : stderr, "%s", HELP);
        return isHelpRequested ? 0 : 84;
    }
    TAILQ_INIT(&client->queue);
    client->p_client = p_client_create(av[1], atoi(av[2]));
    start_cli(client);
    if (client->p_client)
        p_client_close(client->p_client);
    return 0;
}

/*
** EPITECH PROJECT, 2024
** my_teams [WSL: Arch]
** File description:
** client
*/

#include "client.h"
#include "commands.h"
#include "debug_print.h"
#include "protocol.h"

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>

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

static p_payload_t *process_command(char *input, p_client_t *client)
{
    char **args = NULL;
    char *command = NULL;
    p_payload_t *payload = NULL;

    if (!input)
        return NULL;
    args = get_args_from_input(input);
    command = args[0];
    DEBUG_PRINT("Processing command: %s\n", command);
    if (!command)
        return payload;
    for (int i = 0; commands[i].name; i++)
        if (!strcmp(commands[i].name, command))
            payload = commands[i].func(args, (void *)client);
    for (int i = 0; args[i]; i++)
        free(args[i]);
    free(args);
    return payload;
}

static void start_cli(p_client_t *client, queue_head_t *priority_queue)
{
    p_payload_t *payload = NULL;

    if (!client) {
        fprintf(stdout, "Failed to connect to server\n");
        return;
    }
    while (is_running) {
        signal(SIGINT, handle_sigint);
        p_client_listen(client, payload);
        process_priority_queue(priority_queue);
        payload = process_command(get_client_input(), client);
        add_to_priority_queue(payload, priority_queue);
    }
}

int client(int ac, char **av)
{
    int isHelpRequested = ac > 1 && (!strcmp(av[1], "--help")
        || !strcmp(av[1], "-h"));
    p_client_t *client = NULL;
    queue_head_t priority_queue;

    if (ac != 3 || isHelpRequested) {
        fprintf(isHelpRequested ? stdout : stderr, "%s", HELP);
        return isHelpRequested ? 0 : 84;
    }
    TAILQ_INIT(&priority_queue);
    client = p_client_create(av[1], atoi(av[2]));
    start_cli(client, &priority_queue);
    p_client_close(client);
    return 0;
}

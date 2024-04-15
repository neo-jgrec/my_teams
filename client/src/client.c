/*
** EPITECH PROJECT, 2024
** my_teams [WSL: Arch]
** File description:
** client
*/

#include "client.h"
#include "commands.h"
#include "debug_print.h"

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

static void process_response_from_command(p_payload_t response)
{
    if (response.packet_type == EVT_ERROR) {
        fprintf(stdout, "Error: %s\n", response.data);
    } else {
        fprintf(stdout, "%s\n", response.data);
    }
}

static void process_command(char *input)
{
    char **args = get_args_from_input(input);
    char *command = args[0];
    p_payload_t response;

    DEBUG_PRINT("Processing command: %s\n", command);
    for (int i = 0; args[i]; i++)
        DEBUG_PRINT("Arg %d: %s\n", i, args[i]);
    if (!command)
        return;
    for (int i = 0; commands[i].name; i++) {
        if (!strcmp(commands[i].name, command)) {
            DEBUG_PRINT("Command found: %s\n", command);
            response = commands[i].func(args, NULL);
            process_response_from_command(response);
            break;
        }
    }
    for (int i = 0; args[i]; i++)
        free(args[i]);
    free(args);
}

static void start_cli(char *ip, int port)
{
    char *input = NULL;
    p_client_t *client = p_client_create(ip, port);
    p_payload_t *payload = calloc(1, sizeof(p_payload_t));

    if (!client) {
        fprintf(stdout, "Failed to connect to server\n");
        return;
    }
    while (is_running) {
        signal(SIGINT, handle_sigint);
        p_client_listen(client, payload);
        input = get_client_input();
        if (input)
            process_command(input);
    }
    if (payload)
        free(payload);
    p_client_close(client);
}

int client(int ac, char **av)
{
    int isHelpRequested = ac > 1 && (!strcmp(av[1], "--help")
        || !strcmp(av[1], "-h"));

    if (ac != 3 || isHelpRequested) {
        fprintf(isHelpRequested ? stdout : stderr, "%s", HELP);
        return isHelpRequested ? 0 : 84;
    }
    start_cli(av[1], atoi(av[2]));
    return 0;
}

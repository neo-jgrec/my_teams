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

static const char *HELP = "USAGE:"
"\t./myteams_cli ip port\n"
"DESCRIPTION:"
"\tip\tis the server ip address on which the server should connect\n"
"\tport\tis the port number on which the server should connect\n";

static char *get_client_input(void)
{
    char *input = NULL;
    size_t len = 0;

    if (getline(&input, &len, stdin) == -1) {
        free(input);
        return NULL;
    }
    return input;
}

static char **get_args_from_input(char *input)
{
    char **args = malloc(sizeof(char *) * 10);
    char *token = strtok(input, " \n");
    int i = 0;

    for (; token; i++) {
        args[i] = strdup(token);
        token = strtok(NULL, " \n");
    }
    args[i] = NULL;
    return args;
}

static void process_response_from_command(response_t response)
{
    if (response.status == 200 && response.data) {
        dprintf(STDOUT_FILENO, "%d %s\n%s", response.status,
            response.message, (char *)response.data);
        free(response.data);
    } else
        dprintf(STDOUT_FILENO, "%d %s\n", response.status, response.message);
}

static void process_command(char *input)
{
    char **args = get_args_from_input(input);
    char *command = args[0];
    response_t response;

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

static void start_cli(void)
{
    char *input = NULL;

    for (;;) {
        input = get_client_input();
        if (!input)
            break;
        process_command(input);
        free(input);
    }
}

int client(int ac, char **av)
{
    int isHelpRequested = ac > 1 && (!strcmp(av[1], "--help")
        || !strcmp(av[1], "-h"));

    if (ac != 3 || isHelpRequested) {
        dprintf(isHelpRequested ? STDOUT_FILENO : STDERR_FILENO, "%s", HELP);
        return isHelpRequested ? 0 : 84;
    }
    start_cli();
    return 0;
}

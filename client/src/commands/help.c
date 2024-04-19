/*
** EPITECH PROJECT, 2024
** my_teams [WSL: Arch]
** File description:
** help
*/

#include "commands.h"
#include "protocol.h"
#include "unused.h"

#include <stdio.h>

void cmd_help(char **args, UNUSED void *data, UNUSED p_packet_t *packet)
{
    if (!args[0]) {
        fprintf(stdout, "Invalid command\n");
    }
    for (size_t i = 0; commands[i].name; i++) {
        fprintf(stdout, "%-20s: %s\n",
            commands[i].name,
            commands[i].description
        );
    }
}

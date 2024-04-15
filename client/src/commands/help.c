/*
** EPITECH PROJECT, 2024
** my_teams [WSL: Arch]
** File description:
** help
*/

#include "commands.h"
#include "protocol.h"
#include "unused.h"

p_payload_t *cmd_help(char **args, UNUSED void *data)
{
    uint16_t buffer[4096] = {0};
    unsigned long pos = 0;

    if (!args[0])
        return p_create_payload(INT16_MAX - 1, "No arguments provided\n");
    for (int i = 0; commands[i].name; i++) {
        pos += snprintf((char *)buffer + pos, sizeof(buffer) - pos,
            "%s\n", commands[i].name);
        if (pos >= sizeof(buffer))
            break;
    }
    return p_create_payload(INT16_MAX - 1, buffer);
}

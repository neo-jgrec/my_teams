/*
** EPITECH PROJECT, 2024
** my_teams [WSL: Arch]
** File description:
** help
*/

#include "commands.h"
#include "unused.h"
#include <sys/types.h>

p_payload_t cmd_help(char **args, UNUSED void *data)
{
    uint8_t buffer[4096] = {0};
    p_payload_t payload = {
        .packet_type = 0,
        .data = {0},
    };

    if (!args[0]) {
        memcpy(payload.data, "No arguments provided\n", 22);
        return payload;
    }
    unsigned long pos = 0;
    for (int i = 0; commands[i].name; i++) {
        pos += snprintf((char *)buffer + pos, sizeof(buffer) - pos, "%s\n", commands[i].name);
        if (pos >= sizeof(buffer))
            break;
    }
    memcpy(payload.data, buffer, sizeof(buffer));
    return payload;
}

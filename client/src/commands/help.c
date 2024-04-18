/*
** EPITECH PROJECT, 2024
** my_teams [WSL: Arch]
** File description:
** help
*/

#include "commands.h"
#include "protocol.h"
#include "unused.h"

#include <stdint.h>
#include <stdio.h>
#include <string.h>

void cmd_help(char **args, UNUSED void *data, UNUSED p_packet_t *packet)
{
    uint16_t buffer[4096] = {0};
    unsigned long pos = 0;

    if (!args[0]) {
        fprintf(stdout, "Invalid command\n");
    }
    for (int i = 0; commands[i].name; i++) {
        pos += snprintf((char *)buffer + pos, sizeof(buffer) - pos,
            "%s\n", commands[i].name);
        if (pos >= sizeof(buffer))
            break;
    }
    packet->type = 0;
    memcpy(packet->data, buffer, sizeof(packet->data));
}

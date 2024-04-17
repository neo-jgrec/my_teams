/*
** EPITECH PROJECT, 2024
** teams [WSL: Arch]
** File description:
** login
*/

#include "commands.h"
#include "events.h"
#include "protocol.h"

#include <stdio.h>
#include <string.h>

void cmd_login(char **args, void *data, p_packet_t *packet)
{
    size_t nb_args = 0;

    for (; args[nb_args]; nb_args++);
    if (nb_args != 2) {
        packet->type = EVT_ERROR;
        memcpy(packet->data, "Invalid command\n", sizeof("Invalid command\n"));
        return;
    }
    fprintf(stdout, "Trying to log in with username: %s\n", args[1]);
    p_client_send_packet((p_client_t *)data,
        EVT_LOGIN,
        args[1],
        strlen(args[1])
    );
    while (
        !p_client_listen((p_client_t *)data, packet)
        && packet->type != EVT_LOGIN
    );
}

/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** users
*/

#include "client.h"
#include "commands.h"
#include "events.h"
#include "protocol.h"

#include <string.h>

void cmd_users(char **args, void *data, p_packet_t *packet)
{
    size_t nb_args = 0;
    p_client_t *p_client = ((c_client_t *)data)->p_client;

    for (; args[nb_args]; nb_args++);
    if (nb_args != 1) {
        packet->type = EVT_ERROR;
        memcpy(packet->data, "Invalid command\n", sizeof("Invalid command\n"));
        return;
    }
    p_client_send_packet(
        p_client,
        EVT_LIST_USERS,
        NULL,
        0
    );
}

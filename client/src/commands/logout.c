/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** logout
*/

#include "client.h"
#include "commands.h"
#include "events.h"
#include "events_structures.h"
#include "protocol.h"

#include <stdio.h>
#include <string.h>

void cmd_logout(char **args, void *data, p_packet_t *packet)
{
    size_t nb_args = 0;
    p_client_t *p_client = ((c_client_t *)data)->p_client;
    logout_t logout = {0};

    for (; args[nb_args]; nb_args++);
    if (nb_args != 1) {
        packet->type = EVT_ERROR;
        memcpy(packet->data, "Invalid command\n", sizeof("Invalid command\n"));
        return;
    }
    fprintf(stdout, "Trying to log out user with uuid: %s\n", ((c_client_t *)data)->user.uuid);
    memcpy(logout.user_uuid, ((c_client_t *)data)->user.uuid, sizeof(logout.user_uuid));
    p_client_send_packet(
        p_client,
        EVT_DISCONNECT,
        &logout,
        sizeof(logout)
    );
}

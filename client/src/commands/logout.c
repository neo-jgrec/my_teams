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
#include "unused.h"

#include <stdio.h>
#include <string.h>

void cmd_logout(char **args, void *data, UNUSED p_packet_t *packet)
{
    size_t nb_args = 0;
    p_client_t *p_client = ((c_client_t *)data)->p_client;
    team_uuid_t logout = {0};

    for (; args[nb_args]; nb_args++);
    if (nb_args != 1) {
        fprintf(stdout, "Invalid command\n");
    }
    fprintf(stdout, "Trying to log out user with uuid: %s\n",
        ((c_client_t *)data)->user.uuid);
    memcpy(logout.uuid, ((c_client_t *)data)->user.uuid,
        sizeof(logout.uuid));
    // p_client_send_packet(
    //     p_client,
    //     EVT_DISCONNECT,
    //     &logout,
    //     sizeof(logout)
    // );
}

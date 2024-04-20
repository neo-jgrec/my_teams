/*
** EPITECH PROJECT, 2024
** teams [WSL: Arch]
** File description:
** subscribe
*/

#include "client.h"
#include "commands.h"
#include "events.h"
#include "events_structures.h"
#include "protocol.h"
#include "unused.h"

#include <stdio.h>
#include <string.h>

void cmd_unsubscribe(char **args, void *data, UNUSED p_packet_t *packet)
{
    size_t nb_args = 0;
    p_client_t *p_client = ((c_client_t *)data)->p_client;
    unsubscribe_t unsubscribe = {0};

    for (; args[nb_args]; nb_args++);
    if (nb_args != 2) {
        fprintf(stdout, "Invalid command\n");
        return;
    }
    strncpy(unsubscribe.team_uuid, args[1], strlen(args[1]));
    strncpy(unsubscribe.user_uuid, ((c_client_t *)data)->user.uuid,
        strlen(((c_client_t *)data)->user.uuid));
    p_client_send_packet(
        p_client,
        EVT_UNSUBSCRIBE,
        &unsubscribe,
        sizeof(unsubscribe_t)
    );
}

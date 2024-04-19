/*
** EPITECH PROJECT, 2024
** teams [WSL: Arch]
** File description:
** subscribe
*/

#include "client.h"
#include "commands.h"
#include "events.h"
#include "protocol.h"
#include "unused.h"

#include <stdio.h>
#include <string.h>

void cmd_subscribe(char **args, void *data, UNUSED p_packet_t *packet)
{
    size_t nb_args = 0;
    p_client_t *p_client = ((c_client_t *)data)->p_client;
    subscribe_t subscribe = {0};

    for (; args[nb_args]; nb_args++);
    if (nb_args != 2) {
        fprintf(stdout, "Invalid command\n");
        return;
    }
    memcpy(subscribe.team_uuid, args[1], UUID_LENGTH);
    memcpy(subscribe.user_uuid, ((c_client_t *)data)->user.uuid, UUID_LENGTH);
    p_client_send_packet(
        p_client,
        EVT_SUBSCRIBE,
        &subscribe,
        sizeof(subscribe_t)
    );
}

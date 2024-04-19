/*
** EPITECH PROJECT, 2024
** teams [WSL: Arch]
** File description:
** send
*/

#include "client.h"
#include "commands.h"
#include "events.h"
#include "events_structures.h"
#include "protocol.h"
#include "unused.h"

#include <stdio.h>
#include <string.h>

void cmd_send(char **args, void *data, UNUSED p_packet_t *packet)
{
    size_t nb_args = 0;
    p_client_t *p_client = ((c_client_t *)data)->p_client;
    send_message_t m = {0};

    for (; args[nb_args]; nb_args++);
    if (nb_args != 3 || strlen(args[2]) > MAX_BODY_LENGTH) {
        fprintf(stdout,
            (nb_args != 3) ? "Invalid command\n" : "Message too long\n");
        return;
    }
    memcpy(m.receiver_uuid, args[1], sizeof(m.receiver_uuid));
    memcpy(m.message_body, args[2], sizeof(m.message_body));
    memcpy(m.sender_uuid, ((c_client_t *)data)->user.uuid,
        sizeof(m.sender_uuid));
    // p_client_send_packet(
    //     p_client,
    //     EVT_SEND,
    //     &m,
    //     sizeof(m)
    // );
}

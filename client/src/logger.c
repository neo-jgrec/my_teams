/*
** EPITECH PROJECT, 2024
** teams [WSL: Arch]
** File description:
** logger
*/

#include "logging_client.h"
#include "protocol.h"
#include "events.h"
#include "client.h"
#include "events_structures.h"
#include "unused.h"

#include <string.h>
#include <stdio.h>
#include <stdint.h>

static void mt_log_client(UNUSED const p_packet_t *payload)
{
    user_t user = {0};

    memcpy(&user, payload->data, sizeof(user_t));
    client_event_logged_in(user.uuid, user.name);
}

void client_logger(const p_packet_t *payload)
{
    switch (payload->type) {
    case EVT_LOGIN:
        mt_log_client(payload);
        break;
    case INT16_MAX - 1:
        printf("%s\n", payload->data);
        break;
    default:
        printf("no packet type? %d\n", payload->type);
        break;
    }
}

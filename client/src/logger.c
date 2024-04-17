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

#include <string.h>
#include <stdio.h>
#include <stdint.h>

static void mt_log_client(const p_packet_t *payload, c_client_t *client)
{
    user_t user = {0};

    memcpy(&user, payload->data, sizeof(user_t));

    client->user = user;
    client_event_logged_in(user.uuid, user.name);
}

static void mt_logout_client(const p_packet_t *payload, c_client_t *client)
{
    user_t user = {0};

    memcpy(&user, payload->data, sizeof(user_t));

    client->user = user;
    client_event_logged_out(user.uuid, user.name);
    client->user = (user_t){0};
}

void client_logger(const p_packet_t *payload, c_client_t *client)
{
    if (payload->type == EVT_LOGIN)
        mt_log_client(payload, client);
    if (payload->type == EVT_DISCONNECT)
        mt_logout_client(payload, client);
    if (payload->type == INT16_MAX - 1)
        printf("%s\n", payload->data);
}

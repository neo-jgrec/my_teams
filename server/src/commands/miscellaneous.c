/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** miscellaneous
*/

#include "server.h"
#include "unused.h"

void s_server_event_ping(UNUSED s_server_t *server,
    UNUSED const p_payload_t *payload)
{
}

void s_server_event_send_message(UNUSED s_server_t *server,
    const p_payload_t *payload)
{
    send_message_t body;

    memcpy(&body, payload->data, sizeof(send_message_t));
}

void s_server_event_subscribe(UNUSED s_server_t *server,
    const p_payload_t *payload)
{
    subscribe_t body;

    memcpy(&body, payload->data, sizeof(subscribe_t));
}

void s_server_event_unsubscribe(UNUSED s_server_t *server,
    const p_payload_t *payload)
{
    unsubscribe_t body;

    memcpy(&body, payload->data, sizeof(unsubscribe_t));
}

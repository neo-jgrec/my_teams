/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** miscellaneous
*/

#include "server.h"

void s_server_event_ping(s_server_t *server,
    const p_payload_t *payload)
{
    send_success(server, payload);
}

void s_server_event_send_message(s_server_t *server,
    const p_payload_t *payload)
{
    send_message_t body;
    s_private_message_t *message = malloc(sizeof(s_private_message_t));

    if (!message)
        return send_error(server, payload);
    memcpy(&body, payload->data, sizeof(send_message_t));
    strcpy(message->message.sender_uuid, body.sender_uuid);
    strcpy(message->message.receiver_uuid, body.receiver_uuid);
    strcpy(message->message.body, body.message_body);
    TAILQ_INSERT_TAIL(&server->private_messages, message, entries);
    send_success(server, payload);
}

void s_server_event_subscribe(s_server_t *server,
    const p_payload_t *payload)
{
    s_subscribe_t *subscribe;
    subscribe_t body;

    memcpy(&body, payload->data, sizeof(subscribe_t));
    TAILQ_FOREACH(subscribe, &server->subscribes, entries)
        if (strcmp(subscribe->subscribe.user_uuid, body.user_uuid) == 0
            && strcmp(subscribe->subscribe.team_uuid, body.team_uuid) == 0)
            return send_error(server, payload);
    subscribe = malloc(sizeof(s_subscribe_t));
    if (!subscribe)
        return send_error(server, payload);
    strcpy(subscribe->subscribe.user_uuid, body.user_uuid);
    strcpy(subscribe->subscribe.team_uuid, body.team_uuid);
    TAILQ_INSERT_TAIL(&server->subscribes, subscribe, entries);
    send_success(server, payload);
}

void s_server_event_unsubscribe(s_server_t *server,
    const p_payload_t *payload)
{
    s_subscribe_t *subscribe;
    unsubscribe_t body;

    memcpy(&body, payload->data, sizeof(unsubscribe_t));
    TAILQ_FOREACH(subscribe, &server->subscribes, entries)
        if (strcmp(subscribe->subscribe.user_uuid, body.user_uuid) == 0
            && strcmp(subscribe->subscribe.team_uuid, body.team_uuid) == 0) {
            TAILQ_REMOVE(&server->subscribes, subscribe, entries);
            free(subscribe);
            return send_success(server, payload);
        }
    send_error(server, payload);
}
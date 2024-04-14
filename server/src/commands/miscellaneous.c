/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** miscellaneous
*/

#include <time.h>

#include "server.h"

void s_server_event_ping(s_server_t *server,
    const p_payload_t *payload)
{
    send_event(server, payload, EVT_PING);
}

static void ping_user_message(const s_server_t *server,
    const send_message_t *body)
{
    s_logged_user_t *user;
    p_payload_t *payload;

    TAILQ_FOREACH(user, &server->logged, entries) {
        if (strcmp(user->user.uuid, body->receiver_uuid))
            continue;
        payload = p_create_payload(EVT_MESSAGE_RECEIVE, body);
        p_server_send_packet(payload, user->user.socket, server->socket);
    }
}

void s_server_event_send_message(s_server_t *server,
    const p_payload_t *payload)
{
    send_message_t body;
    s_private_message_t *message = malloc(sizeof(s_private_message_t));

    if (!message)
        return send_event(server, payload, EVT_ERROR);
    memcpy(&body, payload->data, sizeof(send_message_t));
    strcpy(message->message.sender_uuid, body.sender_uuid);
    strcpy(message->message.receiver_uuid, body.receiver_uuid);
    strcpy(message->message.body, body.message_body);
    time(&message->message.timestamp);
    TAILQ_INSERT_TAIL(&server->private_messages, message, entries);
    ping_user_message(server, &body);
    send_event(server, payload, EVT_SEND);
}

void s_server_event_subscribe(s_server_t *server,
    const p_payload_t *payload)
{
    s_subscribe_t *subscribe;
    subscribe_t body;

    memcpy(&body, payload->data, sizeof(subscribe_t));
    TAILQ_FOREACH(subscribe, &server->subscribes, entries)
        if (!strcmp(subscribe->subscribe.user_uuid, body.user_uuid)
            && !strcmp(subscribe->subscribe.team_uuid, body.team_uuid))
            return send_event(server, payload, EVT_ERROR_ALREADY);
    subscribe = malloc(sizeof(s_subscribe_t));
    if (!subscribe)
        return send_event(server, payload, EVT_ERROR);
    strcpy(subscribe->subscribe.user_uuid, body.user_uuid);
    strcpy(subscribe->subscribe.team_uuid, body.team_uuid);
    TAILQ_INSERT_TAIL(&server->subscribes, subscribe, entries);
    send_event_body(server, payload, &subscribe->subscribe, EVT_SUBSCRIBE);
}

void s_server_event_unsubscribe(s_server_t *server,
    const p_payload_t *payload)
{
    s_subscribe_t *subscribe;
    unsubscribe_t body;

    memcpy(&body, payload->data, sizeof(unsubscribe_t));
    TAILQ_FOREACH(subscribe, &server->subscribes, entries)
        if (!strcmp(subscribe->subscribe.user_uuid, body.user_uuid)
            && !strcmp(subscribe->subscribe.team_uuid, body.team_uuid)) {
            TAILQ_REMOVE(&server->subscribes, subscribe, entries);
            free(subscribe);
            return send_event_body(server, payload, &body, EVT_UNSUBSCRIBE);
        }
    send_event(server, payload, EVT_ERROR_ALREADY);
}

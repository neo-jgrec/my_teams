/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** miscellaneous
*/

#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "server.h"
#include "events.h"

void s_server_event_ping(s_server_t *server,
    const p_payload_t *payload)
{
    p_server_send_packet_type(EVT_PING, payload->fd, server->socket);
}

static void ping_user_message(const s_server_t *server,
    const send_message_t *body)
{
    s_logged_user_t *user;
    p_packet_t packet = {EVT_MESSAGE_RECEIVE, {0}};

    TAILQ_FOREACH(user, &server->logged, entries) {
        if (strcmp(user->user.uuid, body->receiver_uuid))
            continue;
        memcpy(packet.data, body, sizeof(send_message_t));
        p_server_send_packet(packet, user->user.socket, server->socket);
    }
}

void s_server_event_send_message(s_server_t *server,
    const p_payload_t *payload)
{
    send_message_t body;
    s_private_message_t *message = malloc(sizeof(s_private_message_t));

    if (!message)
        return SEND_TYPE(EVT_ERROR, payload->fd, server->socket);
    memcpy(&body, payload->packet.data, sizeof(send_message_t));
    strcpy(message->message.sender_uuid, body.sender_uuid);
    strcpy(message->message.receiver_uuid, body.receiver_uuid);
    strcpy(message->message.body, body.message_body);
    time(&message->message.timestamp);
    TAILQ_INSERT_TAIL(&server->private_messages, message, entries);
    ping_user_message(server, &body);
    p_server_send_packet_type(EVT_SEND, payload->fd, server->socket);
}

void s_server_event_subscribe(s_server_t *server,
    const p_payload_t *payload)
{
    s_subscribe_t *subscribe;
    subscribe_t body;
    p_packet_t packet = {EVT_SUBSCRIBE, {0}};

    memcpy(&body, payload->packet.data, sizeof(subscribe_t));
    TAILQ_FOREACH(subscribe, &server->subscribes, entries)
        if (!strcmp(subscribe->subscribe.user_uuid, body.user_uuid)
            && !strcmp(subscribe->subscribe.team_uuid, body.team_uuid))
            return SEND_TYPE(EVT_ERROR_ALREADY, payload->fd, server->socket);
    subscribe = malloc(sizeof(s_subscribe_t));
    if (!subscribe)
        return SEND_TYPE(EVT_ERROR, payload->fd, server->socket);
    strcpy(subscribe->subscribe.user_uuid, body.user_uuid);
    strcpy(subscribe->subscribe.team_uuid, body.team_uuid);
    TAILQ_INSERT_TAIL(&server->subscribes, subscribe, entries);
    memcpy(packet.data, &subscribe->subscribe, sizeof(subscribe_t));
    p_server_send_packet(packet, payload->fd, server->socket);
}

void s_server_event_unsubscribe(s_server_t *server,
    const p_payload_t *payload)
{
    s_subscribe_t *subscribe;
    unsubscribe_t body;
    p_packet_t packet = {EVT_UNSUBSCRIBE, {0}};

    memcpy(&body, payload->packet.data, sizeof(unsubscribe_t));
    TAILQ_FOREACH(subscribe, &server->subscribes, entries)
        if (!strcmp(subscribe->subscribe.user_uuid, body.user_uuid)
            && !strcmp(subscribe->subscribe.team_uuid, body.team_uuid)) {
            TAILQ_REMOVE(&server->subscribes, subscribe, entries);
            free(subscribe);
            memcpy(packet.data, &body, sizeof(unsubscribe_t));
            p_server_send_packet(packet, payload->fd, server->socket);
        }
    p_server_send_packet_type(EVT_ERROR_ALREADY, payload->fd, server->socket);
}

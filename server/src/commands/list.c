/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** list
*/

#include <string.h>

#include "server.h"
#include "events.h"

void s_server_event_list_users(s_server_t *server,
    const p_payload_t *payload)
{
    s_user_t *user;
    p_packet_t packet = {EVT_CONTINUE, {0}};

    TAILQ_FOREACH(user, &server->users, entries) {
        if (!TAILQ_NEXT(user, entries))
            break;
        memcpy(packet.data, &user->user, sizeof(user_t));
        p_server_send_packet(packet, payload->fd, server->socket);
    }
    if (!user)
        return SEND_TYPE(EVT_ERROR, payload->fd, server->socket);
    packet.type = EVT_LIST_USERS;
    memcpy(packet.data, &user->user, sizeof(user_t));
    p_server_send_packet(packet, payload->fd, server->socket);
}

void s_server_event_list_messages(s_server_t *server,
    const p_payload_t *payload)
{
    s_private_message_t *message;
    list_messages_t body;
    p_packet_t packet = {EVT_CONTINUE, {0}};

    memcpy(&body, payload->packet.data, sizeof(list_messages_t));
    TAILQ_FOREACH(message, &server->private_messages, entries) {
        if (strcmp(message->message.sender_uuid, body.user_uuid)
            && strcmp(message->message.receiver_uuid, body.user_uuid))
            continue;
        if (packet.data[0])
            p_server_send_packet(packet, payload->fd, server->socket);
        memcpy(packet.data, &message->message, sizeof(private_message_t));
    }
    if (!packet.data[0])
        return SEND_TYPE(EVT_ERROR, payload->fd, server->socket);
    p_server_send_packet(packet, payload->fd, server->socket);
}

void s_server_event_list_subscribed_users_in_team(s_server_t *server,
    const p_payload_t *payload)
{
    s_subscribe_t *subscribe;
    list_subscribed_users_in_team_t body;
    p_packet_t packet = {EVT_CONTINUE, {0}};

    memcpy(&body, payload->packet.data,
        sizeof(list_subscribed_users_in_team_t));
    TAILQ_FOREACH(subscribe, &server->subscribes, entries) {
        if (strcmp(subscribe->subscribe.team_uuid, body.team_uuid))
            continue;
        if (packet.data[0])
            p_server_send_packet(packet, payload->fd, server->socket);
        memcpy(packet.data, &subscribe->subscribe, sizeof(subscribe_t));
    }
    if (!packet.data[0])
        return SEND_TYPE(EVT_ERROR, payload->fd, server->socket);
    packet.type = EVT_LIST_SUBSCRIBED_IN_TEAM;
    p_server_send_packet(packet, payload->fd, server->socket);
}

void s_server_event_list_subscribed_teams(s_server_t *server,
    const p_payload_t *payload)
{
    s_subscribe_t *subscribe;
    list_subscribed_teams_t body;
    p_packet_t packet = {EVT_CONTINUE, {0}};

    memcpy(&body, payload->packet.data, sizeof(list_subscribed_teams_t));
    TAILQ_FOREACH(subscribe, &server->subscribes, entries) {
        if (strcmp(subscribe->subscribe.user_uuid, body.user_uuid))
            continue;
        if (packet.data[0])
            p_server_send_packet(packet, payload->fd, server->socket);
        memcpy(packet.data, &subscribe->subscribe, sizeof(subscribe_t));
    }
    if (!packet.data[0])
        return SEND_TYPE(EVT_ERROR, payload->fd, server->socket);
    packet.type = EVT_LIST_SUBSCRIBED_TEAMS;
    p_server_send_packet(packet, payload->fd, server->socket);
}

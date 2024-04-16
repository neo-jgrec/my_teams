/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** list
*/

#include <string.h>

#include "server.h"

void s_server_event_list_users(s_server_t *server,
    const p_payload_t *payload)
{
    s_user_t *user;
    s_response_t response = {EVT_CONTINUE, 0, sizeof(user_t)};

    TAILQ_FOREACH(user, &server->users, entries) {
        if (!TAILQ_NEXT(user, entries))
            break;
        response.body = &user->user;
        send_event_body(server, payload, &response);
    }
    if (!user)
        return send_event(server, payload, EVT_ERROR);
    response.type = EVT_LIST_USERS;
    response.body = &user->user;
    send_event_body(server, payload, &response);
}

static void send_message(const s_server_t *server, const p_payload_t *payload,
    const private_message_t *message, const event_t type)
{
    p_payload_t response = {0};

    response.packet_type = type;
    memcpy(response.data, message, sizeof(private_message_t));
    p_server_send_packet(&response, payload->client_fd, server->socket);
}

void s_server_event_list_messages(s_server_t *server,
    const p_payload_t *payload)
{
    s_private_message_t *message;
    const private_message_t *tmp = NULL;
    list_messages_t body;

    memcpy(&body, payload->data, sizeof(list_messages_t));
    TAILQ_FOREACH(message, &server->private_messages, entries) {
        if (strcmp(message->message.sender_uuid, body.user_uuid)
            && strcmp(message->message.receiver_uuid, body.user_uuid))
            continue;
        if (tmp)
            send_message(server, payload, tmp, EVT_CONTINUE);
        tmp = &message->message;
    }
    if (!tmp)
        return send_event(server, payload, EVT_ERROR);
    send_message(server, payload, tmp, EVT_LIST_MESSAGES);
}

void s_server_event_list_subscribed_users_in_team(s_server_t *server,
    const p_payload_t *payload)
{
    s_subscribe_t *subscribe;
    list_subscribed_users_in_team_t body;
    s_response_t response = {EVT_CONTINUE, 0, sizeof(subscribe_t)};

    memcpy(&body, payload->data, sizeof(list_subscribed_users_in_team_t));
    TAILQ_FOREACH(subscribe, &server->subscribes, entries) {
        if (strcmp(subscribe->subscribe.team_uuid, body.team_uuid))
            continue;
        if (response.body)
            send_event_body(server, payload, &response);
        response.body = &subscribe->subscribe;
    }
    if (!response.body)
        return send_event(server, payload, EVT_ERROR);
    response.type = EVT_LIST_SUBSCRIBED_IN_TEAM;
    send_event_body(server, payload, &response);
}

void s_server_event_list_subscribed_teams(s_server_t *server,
    const p_payload_t *payload)
{
    s_subscribe_t *subscribe;
    list_subscribed_teams_t body;
    s_response_t response = {EVT_CONTINUE, 0, sizeof(subscribe_t)};

    memcpy(&body, payload->data, sizeof(list_subscribed_teams_t));
    TAILQ_FOREACH(subscribe, &server->subscribes, entries) {
        if (strcmp(subscribe->subscribe.user_uuid, body.user_uuid))
            continue;
        if (response.body)
            send_event_body(server, payload, &response);
        response.body = &subscribe->subscribe;
    }
    if (!response.body)
        return send_event(server, payload, EVT_ERROR);
    response.type = EVT_LIST_SUBSCRIBED_TEAMS;
    send_event_body(server, payload, &response);
}

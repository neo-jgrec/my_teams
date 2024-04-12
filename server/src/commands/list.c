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

    TAILQ_FOREACH(user, &server->users, entries) {
        if (TAILQ_NEXT(user, entries) == NULL)
            break;
        send_event_uuid(server, payload, user->user.uuid, EVT_CONTINUE);
    }
    if (!user)
        return send_event(server, payload, EVT_ERROR);
    send_event_uuid(server, payload, user->user.uuid, EVT_LIST_USERS);
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
        if (strcmp(message->message.sender_uuid, body.user_uuid) != 0
            && strcmp(message->message.receiver_uuid, body.user_uuid) != 0)
            continue;
        if (tmp)
            send_message(server, payload, tmp, EVT_CONTINUE);
        tmp = &message->message;
    }
    if (!tmp)
        return send_event_uuid(server, payload, body.user_uuid, EVT_ERROR);
    send_message(server, payload, tmp, EVT_LIST_MESSAGES);
}

void s_server_event_list_subscribed_users_in_team(s_server_t *server,
    const p_payload_t *payload)
{
    s_subscribe_t *subscribe;
    const subscribe_t *tmp = NULL;
    list_subscribed_users_in_team_t body;

    memcpy(&body, payload->data, sizeof(list_subscribed_users_in_team_t));
    TAILQ_FOREACH(subscribe, &server->subscribes, entries) {
        if (strcmp(subscribe->subscribe.team_uuid, body.team_uuid) != 0)
            continue;
        if (tmp)
            send_event_uuid(server, payload, tmp->user_uuid, EVT_CONTINUE);
        tmp = &subscribe->subscribe;
    }
    if (!tmp)
        return send_event(server, payload, EVT_ERROR);
    send_event_uuid(server, payload, tmp->user_uuid, EVT_LIST_SUBSCRIBED_IN_TEAM);
}

void s_server_event_list_subscribed_teams(s_server_t *server,
    const p_payload_t *payload)
{
    s_subscribe_t *subscribe;
    const subscribe_t *tmp = NULL;
    list_subscribed_teams_t body;

    memcpy(&body, payload->data, sizeof(list_subscribed_teams_t));
    TAILQ_FOREACH(subscribe, &server->subscribes, entries) {
        if (strcmp(subscribe->subscribe.user_uuid, body.user_uuid) != 0)
            continue;
        if (tmp)
            send_event_uuid(server, payload, tmp->team_uuid, EVT_CONTINUE);
        tmp = &subscribe->subscribe;
    }
    if (!tmp)
        return send_event(server, payload, EVT_ERROR);
    send_event_uuid(server, payload, tmp->team_uuid, EVT_LIST_SUBSCRIBED_TEAMS);
}

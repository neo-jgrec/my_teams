/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** list
*/

#include <string.h>

#include "debug_print.h"
#include "server.h"
#include "events.h"

static void set_user_state(const s_server_t *server, user_state_t *response,
    const s_user_t *user)
{
    memcpy(response->uuid, user->user.uuid, UUID_LENGTH);
    memcpy(response->name, user->user.name, MAX_NAME_LENGTH);
    response->is_logged = is_logged(server, user->user.uuid);
}

void s_server_event_list_users(s_server_t *server,
    const p_payload_t *payload)
{
    s_user_t *user;
    p_packet_t packet = {COMBINE(EVT_CONTINUE, EVT_LIST_USERS), {0}};
    user_state_t response;

    TAILQ_FOREACH(user, &server->users, entries) {
        if (!TAILQ_NEXT(user, entries))
            break;
        set_user_state(server, &response, user);
        memcpy(packet.data, &response, sizeof(user_state_t));
        DEBUG_PRINT("List user (name): %s\n", user->user.name);
        p_server_send_packet(&packet, payload->fd, server->socket);
    }
    if (!user)
        return SEND_TYPE(ERROR_PACKET(EVT_ERROR, EVT_LIST_USERS));
    packet.type = EVT_LIST_USERS;
    set_user_state(server, &response, user);
    memcpy(packet.data, &response, sizeof(user_state_t));
    DEBUG_PRINT("List user (name): %s\n", user->user.name);
    p_server_send_packet(&packet, payload->fd, server->socket);
}

void s_server_event_list_messages(s_server_t *server,
    const p_payload_t *payload)
{
    s_private_message_t *message;
    team_uuid_t body;
    p_packet_t packet = {COMBINE(EVT_CONTINUE, EVT_LIST_MESSAGES), {0}};

    memcpy(&body, payload->packet.data, sizeof(team_uuid_t));
    TAILQ_FOREACH(message, &server->private_messages, entries) {
        if (strcmp(message->message.sender_uuid, body.uuid)
            && strcmp(message->message.receiver_uuid, body.uuid))
            continue;
        if (packet.data[0])
            p_server_send_packet(&packet, payload->fd, server->socket);
        DEBUG_PRINT("List message (body): %s\n", message->message.body);
        memcpy(packet.data, &message->message, sizeof(private_message_t));
    }
    if (!packet.data[0])
        return SEND_TYPE(ERROR_PACKET(EVT_ERROR, EVT_LIST_MESSAGES));
    packet.type = EVT_LIST_MESSAGES;
    p_server_send_packet(&packet, payload->fd, server->socket);
}

void s_server_event_list_subscribed_users_in_team(s_server_t *server,
    const p_payload_t *payload)
{
    s_subscribe_t *subscribe;
    team_uuid_t body;
    p_packet_t packet = {COMBINE(EVT_CONTINUE, EVT_LIST_SUBSCRIBED_IN_TEAM),
        {0}};

    memcpy(&body, payload->packet.data, sizeof(team_uuid_t));
    TAILQ_FOREACH(subscribe, &server->subscribes, entries) {
        if (strcmp(subscribe->subscribe.team_uuid, body.uuid))
            continue;
        if (packet.data[0])
            p_server_send_packet(&packet, payload->fd, server->socket);
        DEBUG_PRINT("List subscribe (user): %s\n",
            subscribe->subscribe.user_uuid);
        memcpy(packet.data, &subscribe->subscribe, sizeof(subscribe_t));
    }
    if (!packet.data[0])
        return SEND_TYPE(ERROR_PACKET(EVT_ERROR, EVT_LIST_SUBSCRIBED_IN_TEAM));
    packet.type = EVT_LIST_SUBSCRIBED_IN_TEAM;
    p_server_send_packet(&packet, payload->fd, server->socket);
}

void s_server_event_list_subscribed_teams(s_server_t *server,
    const p_payload_t *payload)
{
    s_subscribe_t *subscribe;
    team_uuid_t body;
    p_packet_t packet = {COMBINE(EVT_CONTINUE, EVT_LIST_SUBSCRIBED_TEAMS),
        {0}};

    memcpy(&body, payload->packet.data, sizeof(team_uuid_t));
    TAILQ_FOREACH(subscribe, &server->subscribes, entries) {
        if (strcmp(subscribe->subscribe.user_uuid, body.uuid))
            continue;
        if (packet.data[0])
            p_server_send_packet(&packet, payload->fd, server->socket);
        DEBUG_PRINT("List team (uuid): %s\n", subscribe->subscribe.team_uuid);
        memcpy(packet.data, &subscribe->subscribe, sizeof(subscribe_t));
    }
    if (!packet.data[0])
        return SEND_TYPE(ERROR_PACKET(EVT_ERROR, EVT_LIST_SUBSCRIBED_TEAMS));
    packet.type = EVT_LIST_SUBSCRIBED_TEAMS;
    p_server_send_packet(&packet, payload->fd, server->socket);
}

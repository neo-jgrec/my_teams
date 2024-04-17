/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** info
*/

#include <string.h>

#include "server.h"
#include "events.h"

void s_server_event_get_user_info(s_server_t *server,
    const p_payload_t *payload)
{
    s_user_t *user;
    team_uuid_t body;
    user_state_t response;
    p_packet_t packet = {EVT_INFO_USER, {0}};

    memcpy(&body, payload->packet.data, sizeof(team_uuid_t));
    TAILQ_FOREACH(user, &server->users, entries)
        if (!strcmp(body.uuid, user->user.uuid)) {
            memcpy(response.uuid, user->user.uuid, UUID_LENGTH);
            memcpy(response.name, user->user.name, MAX_NAME_LENGTH);
            response.is_logged = is_logged(server, user->user.uuid);
            memcpy(packet.data, &response, sizeof(user_state_t));
            p_server_send_packet(&packet, payload->fd, server->socket);
            return;
        }
    SEND_TYPE(ERROR_PACKET(EVT_ERROR_UNKNOWN, EVT_INFO_USER));
}

void s_server_event_get_team_info(s_server_t *server,
    const p_payload_t *payload)
{
    s_team_t *team;
    team_uuid_t body;
    p_packet_t packet = {EVT_INFO_TEAM, {0}};

    memcpy(&body, payload->packet.data, sizeof(team_uuid_t));
    TAILQ_FOREACH(team, &server->teams, entries)
        if (!strcmp(body.uuid, team->team.uuid)) {
            memcpy(packet.data, &team->team, sizeof(team_t));
            p_server_send_packet(&packet, payload->fd, server->socket);
            return;
        }
    SEND_TYPE(ERROR_PACKET(EVT_ERROR_UNKNOWN, EVT_INFO_TEAM));
}

void s_server_event_get_channel_info(s_server_t *server,
    const p_payload_t *payload)
{
    s_channel_t *channel;
    team_uuid_t body;
    p_packet_t packet = {EVT_INFO_CHANNEL, {0}};

    memcpy(&body, payload->packet.data, sizeof(team_uuid_t));
    TAILQ_FOREACH(channel, &server->channels, entries)
        if (!strcmp(body.uuid, channel->channel.uuid)) {
            memcpy(packet.data, &channel->channel, sizeof(channel_t));
            p_server_send_packet(&packet, payload->fd, server->socket);
            return;
        }
    SEND_TYPE(ERROR_PACKET(EVT_ERROR_UNKNOWN, EVT_INFO_CHANNEL));
}

void s_server_event_get_thread_info(s_server_t *server,
    const p_payload_t *payload)
{
    s_thread_t *thread;
    team_uuid_t body;
    p_packet_t packet = {EVT_INFO_THREAD, {0}};

    memcpy(&body, payload->packet.data, sizeof(team_uuid_t));
    TAILQ_FOREACH(thread, &server->threads, entries)
        if (!strcmp(body.uuid, thread->thread.uuid)) {
            memcpy(packet.data, &thread->thread, sizeof(thread_t));
            p_server_send_packet(&packet, payload->fd, server->socket);
        }
    SEND_TYPE(ERROR_PACKET(EVT_ERROR_UNKNOWN, EVT_INFO_THREAD));
}

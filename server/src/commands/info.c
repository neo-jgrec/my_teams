/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** info
*/

#include <string.h>

#include "server.h"

void s_server_event_get_user_info(s_server_t *server,
    const p_payload_t *payload)
{
    s_user_t *user;
    user_info_t body;
    s_response_t response = {EVT_INFO_USER, 0, sizeof(user_info_t)};

    memcpy(&body, payload->data, sizeof(user_info_t));
    TAILQ_FOREACH(user, &server->users, entries)
        if (!strcmp(body.user_uuid, user->user.uuid)) {
            response.body = &user->user;
            return send_event_body(server, payload, &response);
        }
    send_event(server, payload, EVT_ERROR_UNKNOWN);
}

void s_server_event_get_team_info(s_server_t *server,
    const p_payload_t *payload)
{
    s_team_t *team;
    team_info_t body;
    s_response_t response = {EVT_INFO_TEAM, 0, sizeof(team_info_t)};

    memcpy(&body, payload->data, sizeof(team_info_t));
    TAILQ_FOREACH(team, &server->teams, entries)
        if (!strcmp(body.team_uuid, team->team.uuid)) {
            response.body = &team->team;
            return send_event_body(server, payload, &response);
        }
    send_event(server, payload, EVT_ERROR_UNKNOWN);
}

void s_server_event_get_channel_info(s_server_t *server,
    const p_payload_t *payload)
{
    s_channel_t *channel;
    channel_info_t body;
    s_response_t response = {EVT_INFO_CHANNEL, 0, sizeof(channel_info_t)};

    memcpy(&body, payload->data, sizeof(channel_info_t));
    TAILQ_FOREACH(channel, &server->channels, entries)
        if (!strcmp(body.channel_uuid, channel->channel.uuid)) {
            response.body = &channel->channel;
            return send_event_body(server, payload, &response);
        }
    send_event(server, payload, EVT_ERROR_UNKNOWN);
}

void s_server_event_get_thread_info(s_server_t *server,
    const p_payload_t *payload)
{
    s_thread_t *thread;
    thread_info_t body;
    s_response_t response = {EVT_INFO_THREAD, 0, sizeof(thread_info_t)};

    memcpy(&body, payload->data, sizeof(thread_info_t));
    TAILQ_FOREACH(thread, &server->threads, entries)
        if (!strcmp(body.thread_uuid, thread->thread.uuid)) {
            response.body = &thread->thread;
            return send_event_body(server, payload, &response);
        }
    send_event(server, payload, EVT_ERROR_UNKNOWN);
}

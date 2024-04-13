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

    memcpy(&body, payload->data, sizeof(user_info_t));
    TAILQ_FOREACH(user, &server->users, entries)
        if (!strcmp(body.user_uuid, user->user.uuid))
            return send_event_body(server, payload, &user->user, EVT_INFO_USER);
    send_event(server, payload, EVT_ERROR_UNKNOWN);
}

void s_server_event_get_team_info(s_server_t *server,
    const p_payload_t *payload)
{
    s_team_t *team;
    team_info_t body;

    memcpy(&body, payload->data, sizeof(team_info_t));
    TAILQ_FOREACH(team, &server->teams, entries)
        if (!strcmp(body.team_uuid, team->team.uuid))
            return send_event_body(server, payload, &team->team, EVT_INFO_TEAM);
    send_event(server, payload, EVT_ERROR_UNKNOWN);
}

void s_server_event_get_channel_info(s_server_t *server,
    const p_payload_t *payload)
{
    s_channel_t *channel;
    channel_info_t body;

    memcpy(&body, payload->data, sizeof(channel_info_t));
    TAILQ_FOREACH(channel, &server->channels, entries)
        if (!strcmp(body.channel_uuid, channel->channel.uuid))
            return send_event_body(server, payload, &channel->channel,
                EVT_INFO_CHANNEL);
    send_event(server, payload, EVT_ERROR_UNKNOWN);
}

void s_server_event_get_thread_info(s_server_t *server,
    const p_payload_t *payload)
{
    s_thread_t *thread;
    thread_info_t body;

    memcpy(&body, payload->data, sizeof(thread_info_t));
    TAILQ_FOREACH(thread, &server->threads, entries)
        if (!strcmp(body.thread_uuid, thread->thread.uuid))
            return send_event_body(server, payload, &thread->thread,
                EVT_INFO_THREAD);
    send_event(server, payload, EVT_ERROR_UNKNOWN);
}

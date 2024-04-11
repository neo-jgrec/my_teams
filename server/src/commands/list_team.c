/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** list_teams
*/

#include "server.h"

void s_server_event_list_teams(s_server_t *server,
    const p_payload_t *payload)
{
    s_team_t *team;
    const team_t *tmp = NULL;
    list_teams_t body;

    memcpy(&body, payload->data, sizeof(list_teams_t));
    TAILQ_FOREACH(team, &server->teams, entries) {
        if (tmp)
            send_uuid_process(server, payload, tmp->uuid);
        tmp = &team->team;
    }
    if (!tmp)
        return send_error(server, payload);
    send_uuid(server, payload, tmp->uuid);
}

void s_server_event_list_channels(s_server_t *server,
    const p_payload_t *payload)
{
    s_channel_t *channel;
    const channel_t *tmp = NULL;
    list_channels_t body;

    memcpy(&body, payload->data, sizeof(list_channels_t));
    TAILQ_FOREACH(channel, &server->channels, entries) {
        if (strcmp(channel->channel.team_uuid, body.team_uuid) != 0)
            continue;
        if (tmp)
            send_uuid_process(server, payload, tmp->uuid);
        tmp = &channel->channel;
    }
    if (!tmp)
        return send_error(server, payload);
    send_uuid(server, payload, tmp->uuid);
}

void s_server_event_list_threads(s_server_t *server,
    const p_payload_t *payload)
{
    s_channel_t *channel;
    const channel_t *tmp = NULL;
    list_threads_t body;

    memcpy(&body, payload->data, sizeof(list_threads_t));
    TAILQ_FOREACH(channel, &server->channels, entries) {
        if (strcmp(channel->channel.uuid, body.channel_uuid) != 0)
            continue;
        if (tmp)
            send_uuid_process(server, payload, tmp->uuid);
        tmp = &channel->channel;
    }
    if (!tmp)
        return send_error(server, payload);
    send_uuid(server, payload, tmp->uuid);
}

void s_server_event_list_replies(s_server_t *server,
    const p_payload_t *payload)
{
    s_thread_t *thread;
    const thread_t *tmp = NULL;
    list_replies_t body;

    memcpy(&body, payload->data, sizeof(list_replies_t));
    TAILQ_FOREACH(thread, &server->threads, entries) {
        if (strcmp(thread->thread.uuid, body.thread_uuid) != 0)
            continue;
        if (tmp)
            send_uuid_process(server, payload, tmp->uuid);
        tmp = &thread->thread;
    }
    if (!tmp)
        return send_error(server, payload);
    send_uuid(server, payload, tmp->uuid);
}

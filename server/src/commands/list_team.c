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
    list_teams_t body;
    s_response_t response = {EVT_CONTINUE, 0, sizeof(team_t)};

    memcpy(&body, payload->data, sizeof(list_teams_t));
    TAILQ_FOREACH(team, &server->teams, entries) {
        if (response.body)
            send_event_body(server, payload, &response);
        response.body = &team->team;
    }
    if (!response.body)
        return send_event(server, payload, EVT_ERROR);
    response.type = EVT_LIST_TEAMS;
    send_event_body(server, payload, &response);
}

void s_server_event_list_channels(s_server_t *server,
    const p_payload_t *payload)
{
    s_channel_t *channel;
    list_channels_t body;
    s_response_t response = {EVT_CONTINUE, 0, sizeof(channel_t)};

    memcpy(&body, payload->data, sizeof(list_channels_t));
    TAILQ_FOREACH(channel, &server->channels, entries) {
        if (strcmp(channel->channel.team_uuid, body.team_uuid))
            continue;
        if (response.body)
            send_event_body(server, payload, &response);
        response.body = &channel->channel;
    }
    if (!response.body)
        return send_event(server, payload, EVT_ERROR);
    response.type = EVT_LIST_CHANNELS;
    send_event_body(server, payload, &response);
}

void s_server_event_list_threads(s_server_t *server,
    const p_payload_t *payload)
{
    s_channel_t *channel;
    list_threads_t body;
    s_response_t response = {EVT_CONTINUE, 0, sizeof(thread_t)};

    memcpy(&body, payload->data, sizeof(list_threads_t));
    TAILQ_FOREACH(channel, &server->channels, entries) {
        if (strcmp(channel->channel.uuid, body.channel_uuid))
            continue;
        if (response.body)
            send_event_body(server, payload, &response);
        response.body = &channel->channel;
    }
    if (!response.body)
        return send_event(server, payload, EVT_ERROR);
    response.type = EVT_LIST_THREADS;
    send_event_body(server, payload, &response);
}

void s_server_event_list_replies(s_server_t *server,
    const p_payload_t *payload)
{
    s_thread_t *thread;
    list_replies_t body;
    s_response_t response = {EVT_CONTINUE, 0, sizeof(thread_t)};

    memcpy(&body, payload->data, sizeof(list_replies_t));
    TAILQ_FOREACH(thread, &server->threads, entries) {
        if (strcmp(thread->thread.uuid, body.thread_uuid))
            continue;
        if (response.body)
            send_event_body(server, payload, &response);
        response.body = &thread->thread;
    }
    if (!response.body)
        return send_event(server, payload, EVT_ERROR);
    response.type = EVT_LIST_REPLIES;
    send_event_body(server, payload, &response);
}

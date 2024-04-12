/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** info
*/

#include <string.h>

#include "server.h"

static void send_user_info(const s_server_t *server,
    const p_payload_t *payload, const s_user_t *user)
{
    p_payload_t response = {0};

    response.packet_type = EVT_INFO_USER;
    memcpy(response.data, &user->user, sizeof(user_info_t));
    p_server_send_packet(&response, payload->client_fd, server->socket);
}

void s_server_event_get_user_info(s_server_t *server,
    const p_payload_t *payload)
{
    s_user_t *user;
    user_info_t body;

    memcpy(&body, payload->data, sizeof(user_info_t));
    TAILQ_FOREACH(user, &server->users, entries)
        if (strcmp(body.user_uuid, user->user.uuid) == 0)
            return send_user_info(server, payload, user);
    send_event(server, payload, EVT_ERROR_UNKNOWN);
}

static void send_team_info(const s_server_t *server,
    const p_payload_t *payload, const s_team_t *team)
{
    p_payload_t response = {0};

    response.packet_type = EVT_INFO_TEAM;
    memcpy(response.data, &team->team, sizeof(team_info_t));
    p_server_send_packet(&response, payload->client_fd, server->socket);
}

void s_server_event_get_team_info(s_server_t *server,
    const p_payload_t *payload)
{
    s_team_t *team;
    team_info_t body;

    memcpy(&body, payload->data, sizeof(team_info_t));
    TAILQ_FOREACH(team, &server->teams, entries)
        if (strcmp(body.team_uuid, team->team.uuid) == 0)
            return send_team_info(server, payload, team);
    send_event(server, payload, EVT_ERROR_UNKNOWN);
}

static void send_channel_info(const s_server_t *server,
    const p_payload_t *payload, const s_channel_t *channel)
{
    p_payload_t response = {0};

    response.packet_type = EVT_INFO_CHANNEL;
    memcpy(response.data, &channel->channel, sizeof(channel_info_t));
    p_server_send_packet(&response, payload->client_fd, server->socket);
}

void s_server_event_get_channel_info(s_server_t *server,
    const p_payload_t *payload)
{
    s_channel_t *channel;
    channel_info_t body;

    memcpy(&body, payload->data, sizeof(channel_info_t));
    TAILQ_FOREACH(channel, &server->channels, entries)
        if (strcmp(body.channel_uuid, channel->channel.uuid) == 0)
            return send_channel_info(server, payload, channel);
    send_event(server, payload, EVT_ERROR_UNKNOWN);
}

static void send_thread_info(const s_server_t *server,
    const p_payload_t *payload, const s_thread_t *thread)
{
    p_payload_t response = {0};

    response.packet_type = EVT_INFO_THREAD;
    memcpy(response.data, &thread->thread, sizeof(thread_info_t));
    p_server_send_packet(&response, payload->client_fd, server->socket);
}

void s_server_event_get_thread_info(s_server_t *server,
    const p_payload_t *payload)
{
    s_thread_t *thread;
    thread_info_t body;

    memcpy(&body, payload->data, sizeof(thread_info_t));
    TAILQ_FOREACH(thread, &server->threads, entries)
        if (strcmp(body.thread_uuid, thread->thread.uuid) == 0)
            return send_thread_info(server, payload, thread);
    send_event(server, payload, EVT_ERROR_UNKNOWN);
}

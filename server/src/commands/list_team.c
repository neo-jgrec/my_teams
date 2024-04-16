/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** list_teams
*/

#include <string.h>

#include "server.h"
#include "events.h"

void s_server_event_list_teams(s_server_t *server,
    const p_payload_t *payload)
{
    s_team_t *team;
    list_teams_t body;
    p_packet_t packet = {EVT_CONTINUE, {0}};

    memcpy(&body, payload->packet.data, sizeof(list_teams_t));
    TAILQ_FOREACH(team, &server->teams, entries) {
        if (packet.data[0])
            p_server_send_packet(packet, payload->fd, server->socket);
        memcpy(packet.data, &team->team, sizeof(team_t));
    }
    if (!packet.data[0])
        return SEND_TYPE(EVT_ERROR, payload->fd, server->socket);
    packet.type = EVT_LIST_TEAMS;
    p_server_send_packet(packet, payload->fd, server->socket);
}

void s_server_event_list_channels(s_server_t *server,
    const p_payload_t *payload)
{
    s_channel_t *channel;
    list_channels_t body;
    p_packet_t packet = {EVT_CONTINUE, {0}};

    memcpy(&body, payload->packet.data, sizeof(list_channels_t));
    TAILQ_FOREACH(channel, &server->channels, entries) {
        if (strcmp(channel->channel.team_uuid, body.team_uuid))
            continue;
        if (packet.data[0])
            p_server_send_packet(packet, payload->fd, server->socket);
        memcpy(packet.data, &channel->channel, sizeof(channel_t));
    }
    if (!packet.data[0])
        return SEND_TYPE(EVT_ERROR, payload->fd, server->socket);
    packet.type = EVT_LIST_CHANNELS;
    p_server_send_packet(packet, payload->fd, server->socket);
}

void s_server_event_list_threads(s_server_t *server,
    const p_payload_t *payload)
{
    s_channel_t *channel;
    list_threads_t body;
    p_packet_t packet = {EVT_CONTINUE, {0}};

    memcpy(&body, payload->packet.data, sizeof(list_threads_t));
    TAILQ_FOREACH(channel, &server->channels, entries) {
        if (strcmp(channel->channel.uuid, body.channel_uuid))
            continue;
        if (packet.data[0])
            p_server_send_packet(packet, payload->fd, server->socket);
        memcpy(packet.data, &channel->channel, sizeof(channel_t));
    }
    if (!packet.data[0])
        return SEND_TYPE(EVT_ERROR, payload->fd, server->socket);
    packet.type = EVT_LIST_THREADS;
    p_server_send_packet(packet, payload->fd, server->socket);
}

void s_server_event_list_replies(s_server_t *server,
    const p_payload_t *payload)
{
    s_thread_t *thread;
    list_replies_t body;
    // s_response_t response = {EVT_CONTINUE, 0, sizeof(thread_t)};
    p_packet_t packet = {EVT_CONTINUE, {0}};

    memcpy(&body, payload->packet.data, sizeof(list_replies_t));
    TAILQ_FOREACH(thread, &server->threads, entries) {
        if (strcmp(thread->thread.uuid, body.thread_uuid))
            continue;
        if (packet.data[0])
            p_server_send_packet(packet, payload->fd, server->socket);
        memcpy(packet.data, &thread->thread, sizeof(thread_t));
    }
    if (!packet.data[0])
        return SEND_TYPE(EVT_ERROR, payload->fd, server->socket);
    packet.type = EVT_LIST_REPLIES;
    p_server_send_packet(packet, payload->fd, server->socket);
}

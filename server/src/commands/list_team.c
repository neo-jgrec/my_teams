/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** list_teams
*/

#include <string.h>

#include "debug_print.h"
#include "server.h"
#include "events.h"

void s_server_event_list_teams(s_server_t *server,
    const p_payload_t *payload)
{
    s_team_t *team;
    team_uuid_t body;
    p_packet_t packet = {COMBINE(EVT_CONTINUE, EVT_LIST_TEAMS), {0}};

    memcpy(&body, payload->packet.data, sizeof(team_uuid_t));
    if (as_user(server, body.uuid))
        return;
    TAILQ_FOREACH(team, &server->teams, entries) {
        if (packet.data[0])
            p_server_send_packet(&packet, payload->fd, server->socket);
        DEBUG_PRINT("List team (name): %s\n", team->team.name);
        memcpy(packet.data, &team->team, sizeof(team_t));
    }
    if (!packet.data[0])
        return SEND_TYPE(ERROR_PACKET(EVT_ERROR, EVT_LIST_TEAMS));
    packet.type = EVT_LIST_TEAMS;
    p_server_send_packet(&packet, payload->fd, server->socket);
}

void s_server_event_list_channels(s_server_t *server,
    const p_payload_t *payload)
{
    s_channel_t *channel;
    team_uuid_t body;
    p_packet_t packet = {COMBINE(EVT_CONTINUE, EVT_LIST_CHANNELS), {0}};

    memcpy(&body, payload->packet.data, sizeof(team_uuid_t));
    if (!as_team(server, body.uuid))
        return;
    TAILQ_FOREACH(channel, &server->channels, entries) {
        if (strcmp(channel->channel.team_uuid, body.uuid))
            continue;
        if (packet.data[0])
            p_server_send_packet(&packet, payload->fd, server->socket);
        DEBUG_PRINT("List channel (name): %s\n", channel->channel.name);
        memcpy(packet.data, &channel->channel, sizeof(channel_t));
    }
    if (!packet.data[0])
        return SEND_TYPE(ERROR_PACKET(EVT_ERROR, EVT_LIST_CHANNELS));
    packet.type = EVT_LIST_CHANNELS;
    p_server_send_packet(&packet, payload->fd, server->socket);
}

void s_server_event_list_threads(s_server_t *server,
    const p_payload_t *payload)
{
    s_channel_t *channel;
    team_uuid_t body;
    p_packet_t packet = {COMBINE(EVT_CONTINUE, EVT_LIST_THREADS), {0}};

    memcpy(&body, payload->packet.data, sizeof(team_uuid_t));
    if (!as_channel(server, body.uuid))
        return;
    TAILQ_FOREACH(channel, &server->channels, entries) {
        if (strcmp(channel->channel.uuid, body.uuid))
            continue;
        if (packet.data[0])
            p_server_send_packet(&packet, payload->fd, server->socket);
        DEBUG_PRINT("List thread (title): %s\n", channel->channel.name);
        memcpy(packet.data, &channel->channel, sizeof(channel_t));
    }
    if (!packet.data[0])
        return SEND_TYPE(ERROR_PACKET(EVT_ERROR, EVT_LIST_THREADS));
    packet.type = EVT_LIST_THREADS;
    p_server_send_packet(&packet, payload->fd, server->socket);
}

void s_server_event_list_replies(s_server_t *server,
    const p_payload_t *payload)
{
    s_reply_t *reply;
    team_uuid_t body;
    p_packet_t packet = {COMBINE(EVT_CONTINUE, EVT_LIST_REPLIES), {0}};

    memcpy(&body, payload->packet.data, sizeof(team_uuid_t));
    if (!as_channel(server, body.uuid))
        return;
    TAILQ_FOREACH(reply, &server->replies, entries) {
        if (strcmp(reply->reply.thread_uuid, body.uuid))
            continue;
        if (packet.data[0])
            p_server_send_packet(&packet, payload->fd, server->socket);
        DEBUG_PRINT("List reply (body): %s\n", reply->reply.body);
        memcpy(packet.data, &reply->reply, sizeof(reply_t));
    }
    if (!packet.data[0])
        return SEND_TYPE(ERROR_PACKET(EVT_ERROR, EVT_LIST_REPLIES));
    packet.type = EVT_LIST_REPLIES;
    p_server_send_packet(&packet, payload->fd, server->socket);
}

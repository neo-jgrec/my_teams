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
    user_info_t body;
    p_packet_t packet = {EVT_INFO_USER, {0}};

    memcpy(&body, payload->packet.data, sizeof(user_info_t));
    TAILQ_FOREACH(user, &server->users, entries)
        if (!strcmp(body.user_uuid, user->user.uuid)) {
            memcpy(packet.data, &user->user, sizeof(user_t));
            p_server_send_packet(&packet, payload->fd, server->socket);
            return;
        }
    SEND_TYPE(ERROR_PACKET(EVT_ERROR_UNKNOWN, EVT_INFO_USER));
}

void s_server_event_get_team_info(s_server_t *server,
    const p_payload_t *payload)
{
    s_team_t *team;
    team_info_t body;
    p_packet_t packet = {EVT_INFO_TEAM, {0}};

    memcpy(&body, payload->packet.data, sizeof(team_info_t));
    TAILQ_FOREACH(team, &server->teams, entries)
        if (!strcmp(body.team_uuid, team->team.uuid)) {
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
    channel_info_t body;
    p_packet_t packet = {EVT_INFO_CHANNEL, {0}};

    memcpy(&body, payload->packet.data, sizeof(channel_info_t));
    TAILQ_FOREACH(channel, &server->channels, entries)
        if (!strcmp(body.channel_uuid, channel->channel.uuid)) {
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
    thread_info_t body;
    p_packet_t packet = {EVT_INFO_THREAD, {0}};

    memcpy(&body, payload->packet.data, sizeof(thread_info_t));
    TAILQ_FOREACH(thread, &server->threads, entries)
        if (!strcmp(body.thread_uuid, thread->thread.uuid)) {
            memcpy(packet.data, &thread->thread, sizeof(thread_t));
            p_server_send_packet(&packet, payload->fd, server->socket);
        }
    SEND_TYPE(ERROR_PACKET(EVT_ERROR_UNKNOWN, EVT_INFO_THREAD));
}

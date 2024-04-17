/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** check
*/

#include <stdlib.h>
#include <string.h>

#include "server.h"
#include "events.h"

bool check_team_exist(s_server_t *server, const int fd,
    const char *team_uuid, const uint16_t type)
{
    s_team_t *team;
    p_packet_t packet = {COMBINE(EVT_ERROR_UNKNOWN, type), {0}};

    TAILQ_FOREACH(team, &server->teams, entries)
        if (!strcmp(team->team.uuid, team_uuid))
            return true;
    memcpy(packet.data, team_uuid, sizeof(UUID_LENGTH));
    p_server_send_packet(&packet, fd, server->socket);
    return false;
}

bool check_channel_exist(s_server_t *server, const int fd,
    const char *channel_uuid, const uint16_t type)
{
    s_channel_t *channel;
    p_packet_t packet = {COMBINE(EVT_ERROR_UNKNOWN, type), {0}};

    TAILQ_FOREACH(channel, &server->channels, entries)
        if (!strcmp(channel->channel.uuid, channel_uuid))
            return true;
    memcpy(packet.data, channel_uuid, sizeof(UUID_LENGTH));
    p_server_send_packet(&packet, fd, server->socket);
    return false;
}

bool check_thread_exist(s_server_t *server, const int fd,
    const char *thread_uuid, const uint16_t type)
{
    s_thread_t *thread;
    p_packet_t packet = {COMBINE(EVT_ERROR_UNKNOWN, type), {0}};

    TAILQ_FOREACH(thread, &server->threads, entries)
        if (!strcmp(thread->thread.uuid, thread_uuid))
            return true;
    memcpy(packet.data, thread_uuid, sizeof(UUID_LENGTH));
    p_server_send_packet(&packet, fd, server->socket);
    return false;
}

bool check_user_exist(s_server_t *server, const int fd,
    const char *user_uuid, const uint16_t type)
{
    s_user_t *user;
    p_packet_t packet = {COMBINE(EVT_ERROR_UNKNOWN, type), {0}};

    TAILQ_FOREACH(user, &server->users, entries)
        if (!strcmp(user->user.uuid, user_uuid))
            return true;
    memcpy(packet.data, user_uuid, sizeof(UUID_LENGTH));
    p_server_send_packet(&packet, fd, server->socket);
    return false;
}

bool check_uuid(s_server_t *server, const int fd, char **uuid,
    const uint16_t type)
{
    const p_packet_t packet = {COMBINE(EVT_ERROR, type), {0}};

    *uuid = get_uuid();
    if (*uuid)
        return true;
    free(*uuid);
    p_server_send_packet(&packet, fd, server->socket);
    return false;
}

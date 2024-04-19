/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** check
*/

#include <stdlib.h>
#include <string.h>

#include "debug_print.h"
#include "server.h"
#include "events.h"

bool as_team(const s_server_t *server, const char *team_uuid)
{
    s_team_t *team;
    p_packet_t packet = {EVT_ERROR_UNKNOWN_TEAM, {0}};

    TAILQ_FOREACH(team, &server->teams, entries)
        if (!strcmp(team->team.uuid, team_uuid))
            return true;
    memcpy(packet.data, team_uuid, UUID_LENGTH);
    p_server_send_packet(&packet, server->current_fd, server->socket);
    DEBUG_PRINT("Unknown team\n");
    return false;
}

bool as_channel(const s_server_t *server, const char *channel_uuid)
{
    s_channel_t *channel;
    p_packet_t packet = {EVT_ERROR_UNKNOWN_CHANNEL, {0}};

    TAILQ_FOREACH(channel, &server->channels, entries)
        if (!strcmp(channel->channel.uuid, channel_uuid))
            return true;
    memcpy(packet.data, channel_uuid, UUID_LENGTH);
    p_server_send_packet(&packet, server->current_fd, server->socket);
    DEBUG_PRINT("Unknown channel\n");
    return false;
}

bool as_thread(const s_server_t *server, const char *thread_uuid)
{
    s_thread_t *thread;
    p_packet_t packet = {EVT_ERROR_UNKNOWN_THREAD, {0}};

    TAILQ_FOREACH(thread, &server->threads, entries)
        if (!strcmp(thread->thread.uuid, thread_uuid))
            return true;
    memcpy(packet.data, thread_uuid, UUID_LENGTH);
    p_server_send_packet(&packet, server->current_fd, server->socket);
    DEBUG_PRINT("Unknown thread\n");
    return false;
}

bool as_user(const s_server_t *server, const char *user_uuid)
{
    s_user_t *user;
    p_packet_t packet = {EVT_ERROR_UNKNOWN_USER, {0}};

    TAILQ_FOREACH(user, &server->users, entries)
        if (!strcmp(user->user.uuid, user_uuid))
            return true;
    memcpy(packet.data, user_uuid, UUID_LENGTH);
    p_server_send_packet(&packet, server->current_fd, server->socket);
    DEBUG_PRINT("Unknown user\n");
    return false;
}

bool check_uuid(const s_server_t *server, const int fd, char **uuid,
    const uint16_t type)
{
    const p_packet_t packet = {COMBINE(EVT_ERROR, type), {0}};

    *uuid = get_uuid();
    if (*uuid)
        return true;
    free(*uuid);
    p_server_send_packet(&packet, fd, server->socket);
    DEBUG_PRINT("Invalid UUID\n");
    return false;
}

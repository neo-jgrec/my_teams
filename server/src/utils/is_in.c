/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** is_in
*/

#include <string.h>

#include "debug_print.h"
#include "server.h"

bool is_in_teams(const s_server_t *server, const char *user_uuid,
    const char *team_uuid)
{
    s_subscribe_t *subscribe;

    TAILQ_FOREACH(subscribe, &server->subscribes, entries)
        if (!strcmp(subscribe->subscribe.user_uuid, user_uuid)
            && !strcmp(subscribe->subscribe.team_uuid, team_uuid))
            return true;
    DEBUG_PRINT("User %s is not in team %s\n", user_uuid, team_uuid);
    return false;
}

bool is_in_channels(const s_server_t *server, const char *user_uuid,
    const char *channel_uuid)
{
    s_channel_t *channel;

    TAILQ_FOREACH(channel, &server->channels, entries)
        if (!strcmp(channel->channel.uuid, channel_uuid))
            return is_in_teams(server, user_uuid, channel->channel.team_uuid);
    DEBUG_PRINT("User %s is not in channel %s\n", user_uuid, channel_uuid);
    return false;
}

bool is_in_threads(const s_server_t *server, const char *user_uuid,
    const char *thread_uuid)
{
    s_thread_t *thread;

    TAILQ_FOREACH(thread, &server->threads, entries)
        if (!strcmp(thread->thread.uuid, thread_uuid))
            return is_in_channels(server, user_uuid,
                thread->thread.channel_uuid);
    DEBUG_PRINT("User %s is not in thread %s\n", user_uuid, thread_uuid);
    return false;
}

static bool is_in_thread_channel(const s_server_t *server,
    const char *channel_uuid, const char *thread_uuid)
{
    s_thread_t *thread;

    TAILQ_FOREACH(thread, &server->threads, entries)
        if (!strcmp(thread->thread.uuid, thread_uuid)
            && !strcmp(thread->thread.channel_uuid, channel_uuid))
            return true;
    return false;
}

static bool is_in_thread_team(const s_server_t *server, const char *team_uuid,
    const char *thread_uuid)
{
    s_channel_t *channel;

    TAILQ_FOREACH(channel, &server->channels, entries)
        if (!strcmp(channel->channel.team_uuid, team_uuid)
            && is_in_thread_channel(server, channel->channel.uuid,
            thread_uuid))
            return true;
    return false;
}

char *get_thread_team(const s_server_t *server, const char *thread_uuid)
{
    s_team_t *team;

    TAILQ_FOREACH(team, &server->teams, entries)
        if (is_in_thread_team(server, team->team.uuid, thread_uuid))
            return team->team.uuid;
    return NULL;
}

bool is_logged(const s_server_t *server, const char *user_uuid)
{
    s_logged_user_t *logged;

    TAILQ_FOREACH(logged, &server->logged, entries)
        if (!strcmp(logged->user.uuid, user_uuid))
            return true;
    DEBUG_PRINT("User %s is not logged\n", user_uuid);
    return false;
}

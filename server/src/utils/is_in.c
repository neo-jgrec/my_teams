/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** is_in
*/

#include "server.h"

bool is_in_teams(const s_server_t *server, const char *user_uuid,
    const char *team_uuid)
{
    s_subscribe_t *subscribe;

    TAILQ_FOREACH(subscribe, &server->subscribes, entries)
        if (!strcmp(subscribe->subscribe.user_uuid, user_uuid)
            && !strcmp(subscribe->subscribe.team_uuid, team_uuid))
            return true;
    return false;
}

bool is_in_channels(const s_server_t *server, const char *user_uuid,
    const char *channel_uuid)
{
    s_channel_t *channel;

    TAILQ_FOREACH(channel, &server->channels, entries)
        if (!strcmp(channel->channel.uuid, channel_uuid))
            return is_in_teams(server, user_uuid, channel->channel.team_uuid);
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
    return false;
}

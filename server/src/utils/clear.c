/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** clear
*/

#include <stdlib.h>

#include "server.h"

static void clear_users(s_server_t *server)
{
    s_user_t *user;

    while (!TAILQ_EMPTY(&server->users)) {
        user = TAILQ_FIRST(&server->users);
        TAILQ_REMOVE(&server->users, user, entries);
        free(user);
    }
}

static void clear_teams(s_server_t *server)
{
    s_team_t *team;

    while (!TAILQ_EMPTY(&server->teams)) {
        team = TAILQ_FIRST(&server->teams);
        TAILQ_REMOVE(&server->teams, team, entries);
        free(team);
    }
}

static void clear_channels(s_server_t *server)
{
    s_channel_t *channel;

    while (!TAILQ_EMPTY(&server->channels)) {
        channel = TAILQ_FIRST(&server->channels);
        TAILQ_REMOVE(&server->channels, channel, entries);
        free(channel);
    }
}

static void clear_threads(s_server_t *server)
{
    s_thread_t *thread;

    while (!TAILQ_EMPTY(&server->threads)) {
        thread = TAILQ_FIRST(&server->threads);
        TAILQ_REMOVE(&server->threads, thread, entries);
        free(thread);
    }
}

static void clear_replies(s_server_t *server)
{
    s_reply_t *reply;

    while (!TAILQ_EMPTY(&server->replies)) {
        reply = TAILQ_FIRST(&server->replies);
        TAILQ_REMOVE(&server->replies, reply, entries);
        free(reply);
    }
}

static void clear_private_messages(s_server_t *server)
{
    s_private_message_t *private_message;

    while (!TAILQ_EMPTY(&server->private_messages)) {
        private_message = TAILQ_FIRST(&server->private_messages);
        TAILQ_REMOVE(&server->private_messages, private_message, entries);
        free(private_message);
    }
}

static void clear_subscribes(s_server_t *server)
{
    s_subscribe_t *subscribe;

    while (!TAILQ_EMPTY(&server->subscribes)) {
        subscribe = TAILQ_FIRST(&server->subscribes);
        TAILQ_REMOVE(&server->subscribes, subscribe, entries);
        free(subscribe);
    }
}

void clear_server(s_server_t *server)
{
    clear_users(server);
    clear_teams(server);
    clear_channels(server);
    clear_threads(server);
    clear_replies(server);
    clear_private_messages(server);
    clear_subscribes(server);
}

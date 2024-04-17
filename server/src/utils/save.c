/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** save
*/

#include <stdlib.h>
#include <stdio.h>

#include "server.h"

static void save_users(s_server_t *server, FILE *file)
{
    s_user_t *user;
    uint32_t count = 0;

    TAILQ_FOREACH(user, &server->users, entries)
        count++;
    fwrite(&count, sizeof(uint32_t), 1, file);
    while (!TAILQ_EMPTY(&server->users)) {
        user = TAILQ_FIRST(&server->users);
        fwrite(&user->user, sizeof(user_t), 1, file);
        TAILQ_REMOVE(&server->users, user, entries);
        free(user);
    }
}

static void save_teams(s_server_t *server, FILE *file)
{
    s_team_t *team;
    uint32_t count = 0;

    TAILQ_FOREACH(team, &server->teams, entries)
        count++;
    fwrite(&count, sizeof(uint32_t), 1, file);
    while (!TAILQ_EMPTY(&server->teams)) {
        team = TAILQ_FIRST(&server->teams);
        fwrite(&team->team, sizeof(team_t), 1, file);
        TAILQ_REMOVE(&server->teams, team, entries);
        free(team);
    }
}

static void save_channels(s_server_t *server, FILE *file)
{
    s_channel_t *channel;
    uint32_t count = 0;

    TAILQ_FOREACH(channel, &server->channels, entries)
        count++;
    fwrite(&count, sizeof(uint32_t), 1, file);
    while (!TAILQ_EMPTY(&server->channels)) {
        channel = TAILQ_FIRST(&server->channels);
        fwrite(&channel->channel, sizeof(channel_t), 1, file);
        TAILQ_REMOVE(&server->channels, channel, entries);
        free(channel);
    }
}

static void save_threads(s_server_t *server, FILE *file)
{
    s_thread_t *thread;
    uint32_t count = 0;

    TAILQ_FOREACH(thread, &server->threads, entries)
        count++;
    fwrite(&count, sizeof(uint32_t), 1, file);
    while (!TAILQ_EMPTY(&server->threads)) {
        thread = TAILQ_FIRST(&server->threads);
        fwrite(&thread->thread, sizeof(thread_t), 1, file);
        TAILQ_REMOVE(&server->threads, thread, entries);
        free(thread);
    }
}

static void save_replies(s_server_t *server, FILE *file)
{
    s_reply_t *reply;
    uint32_t count = 0;

    TAILQ_FOREACH(reply, &server->replies, entries)
        count++;
    fwrite(&count, sizeof(uint32_t), 1, file);
    while (!TAILQ_EMPTY(&server->replies)) {
        reply = TAILQ_FIRST(&server->replies);
        fwrite(&reply->reply, sizeof(reply_t), 1, file);
        TAILQ_REMOVE(&server->replies, reply, entries);
        free(reply);
    }
}

static void save_private_messages(s_server_t *server, FILE *file)
{
    s_private_message_t *private_message;
    uint32_t count = 0;

    TAILQ_FOREACH(private_message, &server->private_messages, entries)
        count++;
    fwrite(&count, sizeof(uint32_t), 1, file);
    while (!TAILQ_EMPTY(&server->private_messages)) {
        private_message = TAILQ_FIRST(&server->private_messages);
        fwrite(&private_message->message, sizeof(private_message_t), 1, file);
        TAILQ_REMOVE(&server->private_messages, private_message, entries);
        free(private_message);
    }
}

static void save_subscribes(s_server_t *server, FILE *file)
{
    s_subscribe_t *subscribe;
    uint32_t count = 0;

    TAILQ_FOREACH(subscribe, &server->subscribes, entries)
        count++;
    fwrite(&count, sizeof(uint32_t), 1, file);
    while (!TAILQ_EMPTY(&server->subscribes)) {
        subscribe = TAILQ_FIRST(&server->subscribes);
        fwrite(&subscribe->subscribe, sizeof(subscribe_t), 1, file);
        TAILQ_REMOVE(&server->subscribes, subscribe, entries);
        free(subscribe);
    }
}

bool save(s_server_t *server)
{
    FILE *file = fopen(".save", "w");

    if (!file)
        return false;
    save_users(server, file);
    save_teams(server, file);
    save_channels(server, file);
    save_threads(server, file);
    save_replies(server, file);
    save_private_messages(server, file);
    save_subscribes(server, file);
    fclose(file);
    return true;
}

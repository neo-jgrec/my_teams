/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** load
*/

#include <stdio.h>
#include <stdlib.h>

#include "logging_server.h"
#include "debug_print.h"
#include "server.h"

static bool load_users(s_server_t *server, FILE *file)
{
    s_user_t *user;
    uint32_t count;

    if (!fread(&count, sizeof(uint32_t), 1, file))
        return false;
    DEBUG_PRINT("Loading %d users\n", count);
    for (uint32_t i = 0; i < count; i++) {
        user = calloc(1, sizeof(s_user_t));
        if (!user || !fread(&user->user, sizeof(user_t), 1, file))
            return false;
        TAILQ_INSERT_TAIL(&server->users, user, entries);
        server_event_user_loaded(user->user.uuid, user->user.name);
    }
    return true;
}

static bool load_teams(s_server_t *server, FILE *file)
{
    s_team_t *team;
    uint32_t count;

    if (!fread(&count, sizeof(uint32_t), 1, file))
        return false;
    DEBUG_PRINT("Loading %d teams\n", count);
    for (uint32_t i = 0; i < count; i++) {
        team = calloc(1, sizeof(s_team_t));
        if (!team || !fread(&team->team, sizeof(team_t), 1, file))
            return false;
        TAILQ_INSERT_TAIL(&server->teams, team, entries);
    }
    return true;
}

static bool load_channels(s_server_t *server, FILE *file)
{
    s_channel_t *channel;
    uint32_t count;

    if (!fread(&count, sizeof(uint32_t), 1, file))
        return false;
    DEBUG_PRINT("Loading %d channels\n", count);
    for (uint32_t i = 0; i < count; i++) {
        channel = calloc(1, sizeof(s_channel_t));
        if (!channel || !fread(&channel->channel, sizeof(channel_t), 1, file))
            return false;
        TAILQ_INSERT_TAIL(&server->channels, channel, entries);
    }
    return true;
}

static bool load_threads(s_server_t *server, FILE *file)
{
    s_thread_t *thread;
    uint32_t count;

    if (!fread(&count, sizeof(uint32_t), 1, file))
        return false;
    DEBUG_PRINT("Loading %d threads\n", count);
    for (uint32_t i = 0; i < count; i++) {
        thread = calloc(1, sizeof(s_thread_t));
        if (!thread || !fread(&thread->thread, sizeof(thread_t), 1, file))
            return false;
        TAILQ_INSERT_TAIL(&server->threads, thread, entries);
    }
    return true;
}

static bool load_replies(s_server_t *server, FILE *file)
{
    s_reply_t *reply;
    uint32_t count;

    if (!fread(&count, sizeof(uint32_t), 1, file))
        return false;
    DEBUG_PRINT("Loading %d replies\n", count);
    for (uint32_t i = 0; i < count; i++) {
        reply = calloc(1, sizeof(s_reply_t));
        if (!reply || !fread(&reply->reply, sizeof(reply_t), 1, file))
            return false;
        TAILQ_INSERT_TAIL(&server->replies, reply, entries);
    }
    return true;
}

static bool load_private_messages(s_server_t *server, FILE *file)
{
    s_private_message_t *message;
    uint32_t count;

    if (!fread(&count, sizeof(uint32_t), 1, file))
        return false;
    DEBUG_PRINT("Loading %d private messages\n", count);
    for (uint32_t i = 0; i < count; i++) {
        message = calloc(1, sizeof(s_private_message_t));
        if (!message || !fread(&message->message,
            sizeof(private_message_t), 1, file))
            return false;
        TAILQ_INSERT_TAIL(&server->private_messages, message, entries);
    }
    return true;
}

static bool load_subscribes(s_server_t *server, FILE *file)
{
    s_subscribe_t *subscribe;
    uint32_t count;

    if (!fread(&count, sizeof(uint32_t), 1, file))
        return false;
    DEBUG_PRINT("Loading %d subscribes\n", count);
    for (uint32_t i = 0; i < count; i++) {
        subscribe = calloc(1, sizeof(s_subscribe_t));
        if (!subscribe || !fread(&subscribe->subscribe,
            sizeof(subscribe_t), 1, file))
            return false;
        TAILQ_INSERT_TAIL(&server->subscribes, subscribe, entries);
    }
    return true;
}

void load(s_server_t *server)
{
    FILE *file = fopen(SAVE_FILE, "r");
    bool ret;

    if (!file)
        return;
    ret = !load_users(server, file) || !load_teams(server, file)
        || !load_channels(server, file) || !load_threads(server, file)
        || !load_replies(server, file) || !load_private_messages(server, file)
        || !load_subscribes(server, file);
    fclose(file);
    if (ret) {
        remove(SAVE_FILE);
        clear_server(server);
        printf("Error loading server\n");
    } else
        printf("Server loaded\n");
}

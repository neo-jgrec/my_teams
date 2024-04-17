/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** load
*/

#include <stdio.h>
#include <stdlib.h>

#include "server.h"

static void load_users(s_server_t *server, FILE *file)
{
    s_user_t *user = malloc(sizeof(s_user_t));
    uint32_t count;

    if (!user)
        return;
    if (!fread(&count, sizeof(uint32_t), 1, file))
        return;
    for (uint32_t i = 0; i < count; i++) {
        if (!fread(&user->user, sizeof(user_t), 1, file))
            return;
        TAILQ_INSERT_TAIL(&server->users, user, entries);
    }
}

static void load_teams(s_server_t *server, FILE *file)
{
    s_team_t team;
    uint32_t count;

    if (!fread(&count, sizeof(uint32_t), 1, file))
        return;
    for (uint32_t i = 0; i < count; i++) {
        if (!fread(&team, sizeof(s_team_t), 1, file))
            return;
        TAILQ_INSERT_TAIL(&server->teams, &team, entries);
    }
}

static void load_channels(s_server_t *server, FILE *file)
{
    s_channel_t channel;
    uint32_t count;

    if (!fread(&count, sizeof(uint32_t), 1, file))
        return;
    for (uint32_t i = 0; i < count; i++) {
        if (!fread(&channel, sizeof(s_channel_t), 1, file))
            return;
        TAILQ_INSERT_TAIL(&server->channels, &channel, entries);
    }
}

static void load_threads(s_server_t *server, FILE *file)
{
    s_thread_t thread;
    uint32_t count;

    if (!fread(&count, sizeof(uint32_t), 1, file))
        return;
    for (uint32_t i = 0; i < count; i++) {
        if (!fread(&thread, sizeof(s_thread_t), 1, file))
            return;
        TAILQ_INSERT_TAIL(&server->threads, &thread, entries);
    }
}

static void load_replies(s_server_t *server, FILE *file)
{
    s_reply_t reply;
    uint32_t count;

    if (!fread(&count, sizeof(uint32_t), 1, file))
        return;
    for (uint32_t i = 0; i < count; i++) {
        if (!fread(&reply, sizeof(s_reply_t), 1, file))
            return;
        TAILQ_INSERT_TAIL(&server->replies, &reply, entries);
    }
}

static void load_private_messages(s_server_t *server, FILE *file)
{
    s_private_message_t message;
    uint32_t count;

    if (!fread(&count, sizeof(uint32_t), 1, file))
        return;
    for (uint32_t i = 0; i < count; i++) {
        if (!fread(&message, sizeof(s_private_message_t), 1, file))
            return;
        TAILQ_INSERT_TAIL(&server->private_messages, &message, entries);
    }
}

void load(s_server_t *server)
{
    FILE *file = fopen(".save", "r");

    if (!file)
        return;
    load_users(server, file);
    load_teams(server, file);
    load_channels(server, file);
    load_threads(server, file);
    load_replies(server, file);
    load_private_messages(server, file);
    fclose(file);
}

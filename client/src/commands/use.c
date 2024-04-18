/*
** EPITECH PROJECT, 2024
** my_teams [WSL: Arch]
** File description:
** use
*/

#include "client.h"
#include "commands.h"
#include "protocol.h"
#include "unused.h"

#include <stdint.h>
#include <stdio.h>
#include <string.h>

static void no_args(c_client_t *client, UNUSED char **args)
{
    memset(
        client->context.channel_uuid,
        0,
        sizeof(client->context.channel_uuid)
    );
    memset(
        client->context.team_uuid,
        0,
        sizeof(client->context.team_uuid)
    );
    memset(
        client->context.thread_uuid,
        0,
        sizeof(client->context.thread_uuid)
    );
    fprintf(stdout, "Context has been reset\n");
}

static void use_team(c_client_t *client, char **args)
{
    memcpy(
        client->context.team_uuid,
        args[1],
        sizeof(client->context.team_uuid)
    );
    memset(
        client->context.channel_uuid,
        0,
        sizeof(client->context.channel_uuid)
    );
    memset(
        client->context.thread_uuid,
        0,
        sizeof(client->context.thread_uuid)
    );
    fprintf(stdout, "Using team: %s\n", args[1]);
}

static void use_team_and_channel(c_client_t *client, char **args)
{
    memcpy(
        client->context.team_uuid,
        args[1],
        sizeof(client->context.team_uuid)
    );
    memcpy(
        client->context.channel_uuid,
        args[2],
        sizeof(client->context.channel_uuid)
    );
    memset(
        client->context.thread_uuid,
        0,
        sizeof(client->context.thread_uuid)
    );
    fprintf(stdout, "Using team: %s and channel: %s\n", args[1], args[2]);
}

static void use_team_channel_thread(c_client_t *client, char **args)
{
    memcpy(
        client->context.team_uuid,
        args[1],
        sizeof(client->context.team_uuid)
    );
    memcpy(
        client->context.channel_uuid,
        args[2],
        sizeof(client->context.channel_uuid)
    );
    memcpy(
        client->context.thread_uuid,
        args[3],
        sizeof(client->context.thread_uuid)
    );
    fprintf(stdout, "Using team: %s, channel: %s and thread: %s\n",
        args[1],
        args[2],
        args[3]
    );
}

void cmd_use(char **args, void *data, UNUSED p_packet_t *packet)
{
    size_t nb_args = 0;
    static const struct {
        uint8_t nb_args;
        void (*func)(c_client_t *client, char **args);
    } __args_uses[] = {
        {1, no_args},
        {2, use_team},
        {3, use_team_and_channel},
        {4, use_team_channel_thread},
        {0, NULL}
    };

    for (; args[nb_args]; nb_args++);
    for (int i = 0; __args_uses[i].func; i++) {
        if (__args_uses[i].nb_args == nb_args) {
            __args_uses[i].func((c_client_t *)data, args);
            return;
        }
    }
    fprintf(stdout, "Invalid arguments\n");
}

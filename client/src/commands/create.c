/*
** EPITECH PROJECT, 2024
** teams [WSL: Arch]
** File description:
** create
*/

#include "client.h"
#include "commands.h"
#include "events.h"
#include "events_structures.h"
#include "protocol.h"
#include "unused.h"

#include <stdio.h>
#include <string.h>

static int is_empty_context(const context_t *context)
{
    return !strlen(context->team_uuid)
        && !strlen(context->channel_uuid)
        && !strlen(context->thread_uuid);
}

static int is_team_context(const context_t *context)
{
    return strlen(context->team_uuid)
        && !strlen(context->channel_uuid)
        && !strlen(context->thread_uuid);
}

static int is_channel_context(const context_t *context)
{
    return strlen(context->team_uuid)
        && strlen(context->channel_uuid)
        && !strlen(context->thread_uuid);
}

static int is_thread_context(const context_t *context)
{
    return strlen(context->team_uuid)
        && strlen(context->channel_uuid)
        && strlen(context->thread_uuid);
}

static void no_context(c_client_t *client, UNUSED char **args)
{
    p_client_t *p_client = client->p_client;
    team_create_t te = {0};

    memcpy(te.user_uuid, client->user.uuid, sizeof(te.user_uuid));
    memcpy(te.team_name, args[1], sizeof(te.team_name));
    memcpy(te.team_description, args[2], sizeof(te.team_description));
    p_client_send_packet(
        p_client,
        EVT_CREATE_TEAM,
        &te,
        sizeof(te)
    );
}

static void team_context(c_client_t *client, char **args)
{
    p_client_t *p_client = client->p_client;
    channel_create_t c = {0};

    memcpy(c.team_uuid, client->context.team_uuid, sizeof(c.team_uuid));
    memcpy(c.channel_name, args[1], sizeof(c.channel_name));
    memcpy(c.channel_description, args[2], sizeof(c.channel_description));
    p_client_send_packet(
        p_client,
        EVT_CREATE_CHANNEL,
        &c,
        sizeof(c)
    );
}

static void channel_context(c_client_t *client, char **args)
{
    p_client_t *p_client = client->p_client;
    thread_create_t th = {0};

    memcpy(th.channel_uuid,
        client->context.channel_uuid, sizeof(th.channel_uuid));
    memcpy(th.user_uuid, client->user.uuid, sizeof(th.user_uuid));
    memcpy(th.thread_title, args[1], sizeof(th.thread_title));
    memcpy(th.thread_body, args[2], sizeof(th.thread_body));
    p_client_send_packet(
        p_client,
        EVT_CREATE_THREAD,
        &th,
        sizeof(th)
    );
}

static void thread_context(c_client_t *client, char **args)
{
    p_client_t *p_client = client->p_client;
    reply_create_t rep = {0};

    memcpy(rep.thread_uuid,
        client->context.thread_uuid, sizeof(rep.thread_uuid));
    memcpy(rep.user_uuid, client->user.uuid, sizeof(rep.user_uuid));
    memcpy(rep.reply_body, args[1], sizeof(rep.reply_body));
    p_client_send_packet(
        p_client,
        EVT_CREATE_REPLY,
        &rep,
        sizeof(rep)
    );
}

void cmd_create(char **args, void *data, UNUSED p_packet_t *packet)
{
    c_client_t *client = (c_client_t *)data;
    context_t *context = &client->context;
    size_t nb_args = 0;

    for (; args[nb_args]; nb_args++);
    if (nb_args < 2) {
        fprintf(stdout, "Error: Insufficient arguments\n");
        return;
    }
    if (is_empty_context(context))
        no_context(data, args);
    if (is_team_context(context))
        team_context(data, args);
    if (is_channel_context(context))
        channel_context(data, args);
    if (is_thread_context(context))
        thread_context(data, args);
}

/*
** EPITECH PROJECT, 2024
** teams [WSL: Arch]
** File description:
** info
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

void cmd_info(UNUSED char **args, void *data, UNUSED p_packet_t *packet)
{
    c_client_t *client = (c_client_t *)data;
    p_client_t *p_client = client->p_client;
    context_t *context = &client->context;

    if (is_empty_context(context))
        p_client_send_packet(p_client, EVT_INFO_USER, client->user.uuid,
            UUID_LENGTH);
    if (is_team_context(context))
        p_client_send_packet(p_client, EVT_INFO_TEAM, context->team_uuid,
            UUID_LENGTH
        );
    if (is_channel_context(context))
        p_client_send_packet(p_client, EVT_INFO_CHANNEL, context->channel_uuid,
            UUID_LENGTH
        );
    if (is_thread_context(context))
        p_client_send_packet(p_client, EVT_INFO_THREAD, context->thread_uuid,
            UUID_LENGTH
        );
}

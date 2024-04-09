/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** created
*/

#include <string.h>

#include "logging_server.h"
#include "server.h"
#include "unused.h"

void s_server_event_team_created(UNUSED s_server_t *server,
    const p_payload_t *payload)
{
    team_create_t body;
    const char *team_uuid = get_uuid();

    if (!team_uuid)
        return;
    memcpy(&body, payload->data, sizeof(team_create_t));
    server_event_team_created(team_uuid, body.team_name, body.user_uuid);
}

void s_server_event_channel_created(UNUSED s_server_t *server,
    const p_payload_t *payload)
{
    channel_create_t body;
    const char *channel_uuid = get_uuid();

    if (!channel_uuid)
        return;
    memcpy(&body, payload->data, sizeof(channel_create_t));
    server_event_channel_created(body.team_uuid, channel_uuid,
        body.channel_name);
}

void s_server_event_thread_created(UNUSED s_server_t *server,
    const p_payload_t *payload)
{
    thread_create_t body;
    const char *thread_uuid = get_uuid();

    if (!thread_uuid)
        return;
    memcpy(&body, payload->data, sizeof(thread_create_t));
    server_event_thread_created(body.channel_uuid, thread_uuid, body.user_uuid,
        body.thread_title, body.thread_body);
}

void s_server_event_reply_created(UNUSED s_server_t *server,
    const p_payload_t *payload)
{
    reply_create_t body;

    memcpy(&body, payload->data, sizeof(reply_create_t));
    server_event_reply_created(body.channel_uuid, body.user_uuid,
        body.reply_body);
}

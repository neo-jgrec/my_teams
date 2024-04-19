/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** created
*/

#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "logging_server.h"
#include "server.h"
#include "events.h"

static void ping_user_team(const s_server_t *server, const team_t *team)
{
    s_logged_user_t *user;
    p_packet_t packet = {EVT_TEAM_CREATE, {0}};

    memcpy(packet.data, team, sizeof(team_t));
    TAILQ_FOREACH(user, &server->logged, entries)
        p_server_send_packet(&packet, user->user.socket, server->socket);
}

void s_server_event_team_created(s_server_t *server,
    const p_payload_t *payload)
{
    s_team_t *team = calloc(1, sizeof(s_team_t));
    team_create_t body;
    p_packet_t packet = {EVT_CREATE_TEAM, {0}};

    if (!team)
        return SEND_TYPE(ERROR_PACKET(EVT_ERROR, EVT_CREATE_TEAM));
    memcpy(&body, payload->packet.data, sizeof(team_create_t));
    if (!as_user(server, body.user_uuid))
        return;
    get_uuid_no_malloc(team->team.uuid);
    strcpy(team->team.name, body.team_name);
    strcpy(team->team.description, body.team_description);
    TAILQ_INSERT_TAIL(&server->teams, team, entries);
    ping_user_team(server, &team->team);
    server_event_team_created(team->team.uuid, body.team_name, body.user_uuid);
    memcpy(packet.data, &team->team, sizeof(team_t));
    p_server_send_packet(&packet, payload->fd, server->socket);
}

static void ping_user_channel(const s_server_t *server,
    const channel_t *channel)
{
    s_logged_user_t *user;
    p_packet_t packet = {EVT_CHANNEL_CREATE, {0}};

    memcpy(packet.data, channel, sizeof(channel_t));
    TAILQ_FOREACH(user, &server->logged, entries)
        if (is_in_teams(server, user->user.uuid, channel->team_uuid))
            p_server_send_packet(&packet, user->user.socket, server->socket);
}

void s_server_event_channel_created(s_server_t *server,
    const p_payload_t *payload)
{
    s_channel_t *channel = calloc(1, sizeof(s_channel_t));
    channel_create_t body;
    p_packet_t packet = {EVT_CREATE_CHANNEL, {0}};

    if (!channel)
        return SEND_TYPE(ERROR_PACKET(EVT_ERROR, EVT_CREATE_CHANNEL));
    memcpy(&body, payload->packet.data, sizeof(channel_create_t));
    if (!as_team(server, body.team_uuid)
        || !is_in_teams(server, body.user_uuid, body.team_uuid))
        return;
    get_uuid_no_malloc(channel->channel.uuid);
    strcpy(channel->channel.name, body.channel_name);
    strcpy(channel->channel.team_uuid, body.team_uuid);
    strcpy(channel->channel.description, body.channel_description);
    TAILQ_INSERT_TAIL(&server->channels, channel, entries);
    ping_user_channel(server, &channel->channel);
    server_event_channel_created(body.team_uuid,
        channel->channel.uuid, body.channel_name);
    memcpy(packet.data, &channel->channel, sizeof(channel_t));
    p_server_send_packet(&packet, payload->fd, server->socket);
}

static void ping_user_thread(const s_server_t *server,
    const thread_t *thread)
{
    s_logged_user_t *user;
    p_packet_t packet = {EVT_THREAD_CREATE, {0}};

    memcpy(packet.data, thread, sizeof(thread_t));
    TAILQ_FOREACH(user, &server->logged, entries)
        if (is_in_channels(server, user->user.uuid, thread->channel_uuid))
            p_server_send_packet(&packet, user->user.socket, server->socket);
}

static void set_thread(s_server_t *server, s_thread_t *thread,
    const thread_create_t *body)
{
    get_uuid_no_malloc(thread->thread.uuid);
    strcpy(thread->thread.user_uuid, body->user_uuid);
    strcpy(thread->thread.channel_uuid, body->channel_uuid);
    strcpy(thread->thread.title, body->thread_title);
    strcpy(thread->thread.body, body->thread_body);
    time(&thread->thread.timestamp);
    TAILQ_INSERT_TAIL(&server->threads, thread, entries);
    ping_user_thread(server, &thread->thread);
}

void s_server_event_thread_created(s_server_t *server,
    const p_payload_t *payload)
{
    s_thread_t *thread = calloc(1, sizeof(s_thread_t));
    thread_create_t body;
    p_packet_t packet = {EVT_CREATE_THREAD, {0}};

    if (!thread)
        return SEND_TYPE(ERROR_PACKET(EVT_ERROR, packet.type));
    memcpy(&body, payload->packet.data, sizeof(thread_create_t));
    if (!as_channel(server, body.channel_uuid)
        || !as_user(server, body.user_uuid)
        || !is_in_channels(server, body.user_uuid, body.channel_uuid))
        return;
    set_thread(server, thread, &body);
    server_event_thread_created(body.channel_uuid, thread->thread.uuid,
        body.user_uuid, body.thread_title, body.thread_body);
    memcpy(packet.data, &thread->thread, sizeof(thread_t));
    p_server_send_packet(&packet, payload->fd, server->socket);
}

static void ping_user_reply(const s_server_t *server,
    const reply_create_t *body)
{
    s_logged_user_t *user;
    p_packet_t packet = {EVT_REPLY_CREATE, {0}};
    reply_ref_t reply;
    s_team_t *team;

    TAILQ_FOREACH(team, &server->teams, entries)
        if (!strcmp(body->thread_uuid, team->team.uuid))
            memcpy(reply.team_uuid, team->team.uuid, UUID_LENGTH);
    if (!reply.team_uuid[0])
        return;
    memcpy(packet.data, body, sizeof(reply_create_t));
    TAILQ_FOREACH(user, &server->logged, entries)
        if (is_in_threads(server, user->user.uuid, body->thread_uuid)) {
            memcpy(reply.user_uuid, body->user_uuid, UUID_LENGTH);
            memcpy(reply.thread_uuid, body->thread_uuid, UUID_LENGTH);
            memcpy(reply.reply_body, body->reply_body, MAX_BODY_LENGTH);
            p_server_send_packet(&packet, user->user.socket, server->socket);
        }
}

static void set_reply(s_reply_t *reply, const reply_create_t *body)
{
    strcpy(reply->reply.user_uuid, body->user_uuid);
    strcpy(reply->reply.thread_uuid, body->thread_uuid);
    strcpy(reply->reply.body, body->reply_body);
    time(&reply->reply.timestamp);
}

void s_server_event_reply_created(s_server_t *server,
    const p_payload_t *payload)
{
    s_reply_t *reply = calloc(1, sizeof(s_reply_t));
    reply_create_t body;
    p_packet_t packet = {EVT_CREATE_REPLY, {0}};

    if (!reply)
        return SEND_TYPE(ERROR_PACKET(EVT_ERROR, packet.type));
    memcpy(&body, payload->packet.data, sizeof(reply_create_t));
    set_reply(reply, &body);
    if (!as_thread(server, body.thread_uuid)
        || !as_user(server, body.user_uuid)
        || !is_in_threads(server, body.user_uuid, body.thread_uuid))
        return;
    TAILQ_INSERT_TAIL(&server->replies, reply, entries);
    ping_user_reply(server, &body);
    server_event_reply_created(body.thread_uuid, body.user_uuid,
        body.reply_body);
    memcpy(packet.data, &reply->reply, sizeof(reply_t));
    p_server_send_packet(&packet, payload->fd, server->socket);
}

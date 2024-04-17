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

static void ping_user_team(const s_server_t *server, team_create_t *body)
{
    s_logged_user_t *user;
    p_packet_t packet = {EVT_TEAM_CREATE, {0}};

    memcpy(packet.data, body, sizeof(team_create_t));
    TAILQ_FOREACH(user, &server->logged, entries)
        p_server_send_packet(&packet, user->user.socket, server->socket);
}

void s_server_event_team_created(s_server_t *server,
    const p_payload_t *payload)
{
    s_team_t *team = malloc(sizeof(s_team_t));
    team_create_t body;
    const char *team_uuid;
    p_packet_t packet = {EVT_TEAM_CREATE, {0}};

    if (!team)
        return SEND_TYPE(ERROR_PACKET(EVT_ERROR, EVT_TEAM_CREATE));
    team_uuid = get_uuid();
    if (!team_uuid) {
        free(team);
        return SEND_TYPE(ERROR_PACKET(EVT_ERROR, EVT_TEAM_CREATE));
    }
    memcpy(&body, payload->packet.data, sizeof(team_create_t));
    strcpy(team->team.uuid, team_uuid);
    strcpy(team->team.name, body.team_name);
    TAILQ_INSERT_TAIL(&server->teams, team, entries);
    ping_user_team(server, &body);
    server_event_team_created(team_uuid, body.team_name, body.user_uuid);
    memcpy(packet.data, &team->team, sizeof(team_t));
    p_server_send_packet(&packet, payload->fd, server->socket);
}

static void ping_user_channel(const s_server_t *server,
    const channel_create_t *body)
{
    s_logged_user_t *user;
    p_packet_t packet = {EVT_CHANNEL_CREATE, {0}};

    memcpy(packet.data, body, sizeof(channel_create_t));
    TAILQ_FOREACH(user, &server->logged, entries)
        if (is_in_teams(server, user->user.uuid, body->team_uuid))
            p_server_send_packet(&packet, user->user.socket, server->socket);
}

void s_server_event_channel_created(s_server_t *server,
    const p_payload_t *payload)
{
    s_channel_t *channel = malloc(sizeof(s_channel_t));
    channel_create_t body;
    const char *chan_uuid;
    p_packet_t packet = {EVT_CHANNEL_CREATE, {0}};

    if (!channel)
        return SEND_TYPE(ERROR_PACKET(EVT_ERROR, EVT_CHANNEL_CREATE));
    chan_uuid = get_uuid();
    if (!chan_uuid) {
        free(channel);
        return SEND_TYPE(ERROR_PACKET(EVT_ERROR, EVT_CHANNEL_CREATE));
    }
    memcpy(&body, payload->packet.data, sizeof(channel_create_t));
    strcpy(channel->channel.uuid, chan_uuid);
    strcpy(channel->channel.name, body.channel_name);
    TAILQ_INSERT_TAIL(&server->channels, channel, entries);
    ping_user_channel(server, &body);
    server_event_channel_created(body.team_uuid, chan_uuid, body.channel_name);
    memcpy(packet.data, &channel->channel, sizeof(channel_t));
    p_server_send_packet(&packet, payload->fd, server->socket);
}

static void ping_user_thread(const s_server_t *server,
    const thread_create_t *body)
{
    s_logged_user_t *user;
    p_packet_t packet = {EVT_THREAD_CREATE, {0}};

    memcpy(packet.data, body, sizeof(thread_create_t));
    TAILQ_FOREACH(user, &server->logged, entries)
        if (is_in_channels(server, user->user.uuid, body->channel_uuid))
            p_server_send_packet(&packet, user->user.socket, server->socket);
}

static void set_thread(s_thread_t *thread, const thread_create_t *body,
    const char *thread_uuid)
{
    strcpy(thread->thread.uuid, thread_uuid);
    strcpy(thread->thread.channel_uuid, body->channel_uuid);
    strcpy(thread->thread.title, body->thread_title);
    strcpy(thread->thread.body, body->thread_body);
    time(&thread->thread.timestamp);
}

void s_server_event_thread_created(s_server_t *server,
    const p_payload_t *payload)
{
    s_thread_t *thread = malloc(sizeof(s_thread_t));
    thread_create_t body;
    const char *thread_uuid;
    p_packet_t packet = {EVT_THREAD_CREATE, {0}};

    if (!thread)
        return SEND_TYPE(ERROR_PACKET(EVT_ERROR, EVT_THREAD_CREATE));
    thread_uuid = get_uuid();
    if (!thread_uuid) {
        free(thread);
        return SEND_TYPE(ERROR_PACKET(EVT_ERROR, EVT_THREAD_CREATE));
    }
    memcpy(&body, payload->packet.data, sizeof(thread_create_t));
    set_thread(thread, &body, thread_uuid);
    TAILQ_INSERT_TAIL(&server->threads, thread, entries);
    ping_user_thread(server, &body);
    server_event_thread_created(body.channel_uuid, thread_uuid, body.user_uuid,
        body.thread_title, body.thread_body);
    memcpy(packet.data, &thread->thread, sizeof(thread_t));
    p_server_send_packet(&packet, payload->fd, server->socket);
}

static void ping_user_reply(const s_server_t *server,
    const reply_create_t *body)
{
    s_logged_user_t *user;
    p_packet_t packet = {EVT_REPLY_CREATE, {0}};

    memcpy(packet.data, body, sizeof(reply_create_t));
    TAILQ_FOREACH(user, &server->logged, entries)
        if (is_in_threads(server, user->user.uuid, body->thread_uui))
            p_server_send_packet(&packet, user->user.socket, server->socket);
}

void s_server_event_reply_created(s_server_t *server,
    const p_payload_t *payload)
{
    s_reply_t *reply = malloc(sizeof(s_reply_t));
    reply_create_t body;
    p_packet_t packet = {EVT_REPLY_CREATE, {0}};

    if (!reply)
        return SEND_TYPE(ERROR_PACKET(EVT_ERROR, EVT_REPLY_CREATE));
    memcpy(&body, payload->packet.data, sizeof(reply_create_t));
    strcpy(reply->reply.user_uuid, body.user_uuid);
    strcpy(reply->reply.thread_uuid, body.thread_uui);
    strcpy(reply->reply.body, body.reply_body);
    time(&reply->reply.timestamp);
    TAILQ_INSERT_TAIL(&server->replies, reply, entries);
    ping_user_reply(server, &body);
    server_event_reply_created(body.thread_uui, body.user_uuid,
        body.reply_body);
    memcpy(packet.data, &reply->reply, sizeof(reply_t));
    p_server_send_packet_type(EVT_REPLY_CREATE, payload->fd, server->socket);
}

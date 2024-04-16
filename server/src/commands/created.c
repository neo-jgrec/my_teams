/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** created
*/

#include <string.h>
#include <time.h>

#include "logging_server.h"
#include "server.h"

static void ping_user_team(const s_server_t *server,
    const p_payload_t *payload, team_create_t *body)
{
    s_logged_user_t *user;
    const s_response_t response = {EVT_TEAM_CREATE, body->team_name,
        sizeof(team_t)};

    TAILQ_FOREACH(user, &server->logged, entries)
        send_event_body(server, payload, &response);
}

void s_server_event_team_created(s_server_t *server,
    const p_payload_t *payload)
{
    s_team_t *team = malloc(sizeof(s_team_t));
    team_create_t body;
    const char *team_uuid;
    s_response_t response;

    if (!team)
        return send_event(server, payload, EVT_ERROR);
    team_uuid = get_uuid();
    if (!team_uuid) {
        free(team);
        return send_event(server, payload, EVT_ERROR);
    }
    memcpy(&body, payload->data, sizeof(team_create_t));
    strcpy(team->team.uuid, team_uuid);
    strcpy(team->team.name, body.team_name);
    TAILQ_INSERT_TAIL(&server->teams, team, entries);
    ping_user_team(server, payload, &body);
    server_event_team_created(team_uuid, body.team_name, body.user_uuid);
    response = (s_response_t){EVT_TEAM_CREATE, &team->team, sizeof(team_t)};
    send_event_body(server, payload, &response);
}

static void ping_user_channel(const s_server_t *server,
    const channel_create_t *body)
{
    p_payload_t *payload = p_create_payload(EVT_CHANNEL_CREATE, body);
    s_logged_user_t *user;

    TAILQ_FOREACH(user, &server->logged, entries)
        if (is_in_teams(server, user->user.uuid, body->team_uuid))
            p_server_send_packet(payload, user->user.socket, server->socket);
}

void s_server_event_channel_created(s_server_t *server,
    const p_payload_t *payload)
{
    s_channel_t *channel = malloc(sizeof(s_channel_t));
    channel_create_t body;
    const char *chan_uuid;
    s_response_t response = {EVT_CHANNEL_CREATE, 0, sizeof(channel_t)};

    if (!channel)
        return send_event(server, payload, EVT_ERROR);
    chan_uuid = get_uuid();
    if (!chan_uuid) {
        free(channel);
        return send_event(server, payload, EVT_ERROR);
    }
    memcpy(&body, payload->data, sizeof(channel_create_t));
    strcpy(channel->channel.uuid, chan_uuid);
    strcpy(channel->channel.name, body.channel_name);
    TAILQ_INSERT_TAIL(&server->channels, channel, entries);
    ping_user_channel(server, &body);
    server_event_channel_created(body.team_uuid, chan_uuid, body.channel_name);
    response.body = &channel->channel;
    send_event_body(server, payload, &response);
}

static void ping_user_thread(const s_server_t *server,
    const thread_create_t *body)
{
    p_payload_t *payload = p_create_payload(EVT_CHANNEL_CREATE, body);
    s_logged_user_t *user;

    TAILQ_FOREACH(user, &server->logged, entries)
        if (is_in_channels(server, user->user.uuid, body->channel_uuid))
            p_server_send_packet(payload, user->user.socket, server->socket);
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
    s_response_t response = {EVT_THREAD_CREATE, 0, sizeof(thread_t)};

    if (!thread)
        return send_event(server, payload, EVT_ERROR);
    thread_uuid = get_uuid();
    if (!thread_uuid) {
        free(thread);
        return send_event(server, payload, EVT_ERROR);
    }
    memcpy(&body, payload->data, sizeof(thread_create_t));
    set_thread(thread, &body, thread_uuid);
    TAILQ_INSERT_TAIL(&server->threads, thread, entries);
    ping_user_thread(server, &body);
    server_event_thread_created(body.channel_uuid, thread_uuid, body.user_uuid,
        body.thread_title, body.thread_body);
    response.body = &thread->thread;
    send_event_body(server, payload, &response);
}

static void ping_user_reply(const s_server_t *server,
    const reply_create_t *body)
{
    p_payload_t *payload = p_create_payload(EVT_REPLY_CREATE, body);
    s_logged_user_t *user;

    TAILQ_FOREACH(user, &server->logged, entries)
        if (is_in_threads(server, user->user.uuid, body->thread_uui))
            p_server_send_packet(payload, user->user.socket, server->socket);
}

void s_server_event_reply_created(s_server_t *server,
    const p_payload_t *payload)
{
    s_reply_t *reply = malloc(sizeof(s_reply_t));
    reply_create_t body;
    s_response_t response = {EVT_REPLY_CREATE, 0, sizeof(reply_t)};

    if (!reply)
        return send_event(server, payload, EVT_ERROR);
    memcpy(&body, payload->data, sizeof(reply_create_t));
    strcpy(reply->reply.user_uuid, body.user_uuid);
    strcpy(reply->reply.thread_uuid, body.thread_uui);
    strcpy(reply->reply.body, body.reply_body);
    time(&reply->reply.timestamp);
    TAILQ_INSERT_TAIL(&server->replies, reply, entries);
    ping_user_reply(server, &body);
    server_event_reply_created(body.thread_uui, body.user_uuid,
        body.reply_body);
    response.body = &reply->reply;
    send_event_body(server, payload, &response);
}

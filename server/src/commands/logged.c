/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** logged
*/

#include <string.h>
#include <stdlib.h>

#include "logging_server.h"
#include "server.h"
#include "events.h"

static void add_logged_user(s_server_t *server, const p_payload_t *payload,
    s_user_t *user)
{
    s_logged_user_t *logged = malloc(sizeof(s_logged_user_t));

    if (!logged) {
        free(user);
        return SEND_TYPE(EVT_ERROR, payload->fd, server->socket);
    }
    logged->user.socket = payload->fd;
    strcpy(logged->user.uuid, user->user.uuid);
    strcpy(logged->user.name, user->user.name);
    TAILQ_INSERT_TAIL(&server->logged, logged, entries);
}

static void new_user(s_server_t *server, const p_payload_t *payload,
    const login_t *body)
{
    s_user_t *user = malloc(sizeof(s_user_t));
    const char *user_uuid;
    p_packet_t packet = {EVT_LOGIN, {0}};

    if (!user)
        return SEND_TYPE(EVT_ERROR, payload->fd, server->socket);
    user_uuid = get_uuid();
    if (!user_uuid) {
        free(user);
        return SEND_TYPE(EVT_ERROR, payload->fd, server->socket);
    }
    strcpy(user->user.uuid, user_uuid);
    strcpy(user->user.name, body->user_name);
    TAILQ_INSERT_TAIL(&server->users, user, entries);
    add_logged_user(server, payload, user);
    server_event_user_logged_in(user_uuid);
    memcpy(packet.data, &user->user, sizeof(user_t));
    p_server_send_packet(packet, payload->fd, server->socket);
}

void s_server_event_logged_in(s_server_t *server,
    const p_payload_t *payload)
{
    s_user_t *user;
    s_logged_user_t *logged;
    login_t body;
    p_packet_t packet = {EVT_LOGIN, {0}};

    memcpy(&body, payload->packet.data, sizeof(login_t));
    TAILQ_FOREACH(logged, &server->logged, entries)
        if (!strcmp(body.user_name, logged->user.name))
            return SEND_TYPE(EVT_ERROR_ALREADY, payload->fd, server->socket);
    TAILQ_FOREACH(user, &server->users, entries)
        if (!strcmp(body.user_name, user->user.name)) {
            add_logged_user(server, payload, user);
            server_event_user_logged_in(user->user.uuid);
            memcpy(packet.data, &user->user, sizeof(user_t));
            p_server_send_packet(packet, payload->fd, server->socket);
            return;
        }
    new_user(server, payload, &body);
}

void s_server_event_logged_out(s_server_t *server,
    const p_payload_t *payload)
{
    s_logged_user_t *user;
    logout_t body;
    p_packet_t packet = {EVT_DISCONNECT, {0}};
    user_t user_response;

    memcpy(&body, payload->packet.data, sizeof(logout_t));
    TAILQ_FOREACH(user, &server->logged, entries)
        if (!strcmp(body.user_uuid, user->user.uuid)) {
            TAILQ_REMOVE(&server->logged, user, entries);
            break;
        }
    if (!user)
        return SEND_TYPE(EVT_ERROR_UNKNOWN, payload->fd, server->socket);
    server_event_user_logged_out(body.user_uuid);
    strcpy(user_response.uuid, user->user.uuid);
    strcpy(user_response.name, user->user.name);
    memcpy(packet.data, &user_response, sizeof(user_t));
    p_server_send_packet(packet, payload->fd, server->socket);
}

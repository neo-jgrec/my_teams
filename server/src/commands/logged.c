/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** logged
*/

#include <string.h>

#include "logging_server.h"
#include "server.h"

static void add_logged_user(s_server_t *server, const p_payload_t *payload,
    s_user_t *user)
{
    s_logged_user_t *logged = malloc(sizeof(s_logged_user_t));

    if (!logged) {
        free(user);
        return send_event(server, payload, EVT_ERROR);
    }
    logged->user.socket = payload->client_fd;
    strcpy(logged->user.uuid, user->user.uuid);
    strcpy(logged->user.name, user->user.name);
    TAILQ_INSERT_TAIL(&server->logged, logged, entries);
}

static void new_user(s_server_t *server, const p_payload_t *payload,
    const login_t *body)
{
    s_user_t *user = malloc(sizeof(s_user_t));
    const char *user_uuid;

    if (!user)
        return send_event(server, payload, EVT_ERROR);
    user_uuid = get_uuid();
    if (!user_uuid) {
        free(user);
        return send_event(server, payload, EVT_ERROR);
    }
    strcpy(user->user.uuid, user_uuid);
    strcpy(user->user.name, body->user_name);
    TAILQ_INSERT_TAIL(&server->users, user, entries);
    add_logged_user(server, payload, user);
    server_event_user_logged_in(user_uuid);
    send_event_body(server, payload, &user->user, EVT_LOGIN);
}

void s_server_event_logged_in(s_server_t *server,
    const p_payload_t *payload)
{
    s_user_t *user;
    s_logged_user_t *logged;
    login_t body;

    memcpy(&body, payload->data, sizeof(login_t));
    TAILQ_FOREACH(logged, &server->logged, entries)
        if (!strcmp(body.user_name, logged->user.name))
            return send_event(server, payload, EVT_ERROR_ALREADY);
    TAILQ_FOREACH(user, &server->users, entries)
        if (!strcmp(body.user_name, user->user.name)) {
            add_logged_user(server, payload, user);
            server_event_user_logged_in(user->user.uuid);
            return send_event_body(server, payload, &user->user, EVT_LOGIN);
        }
    new_user(server, payload, &body);
}

void s_server_event_logged_out(s_server_t *server,
    const p_payload_t *payload)
{
    s_logged_user_t *user;
    logout_t body;

    memcpy(&body, payload->data, sizeof(logout_t));
    TAILQ_FOREACH(user, &server->logged, entries)
        if (!strcmp(body.user_uuid, user->user.uuid)) {
            TAILQ_REMOVE(&server->logged, user, entries);
            break;
        }
    if (!user)
        return send_event(server, payload, EVT_ERROR_ALREADY);
    server_event_user_logged_out(body.user_uuid);
    send_event_body(server, payload, &user->user, EVT_DISCONNECT);
}

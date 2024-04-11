/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** logged
*/

#include <string.h>

#include "logging_server.h"
#include "server.h"

static void new_user(s_server_t *server, const p_payload_t *payload,
    const login_t *body)
{
    s_user_t *user = malloc(sizeof(s_user_t));
    const char *user_uuid;

    if (!user)
        return send_error(server, payload);
    user_uuid = get_uuid();
    if (!user_uuid) {
        free(user);
        return send_error(server, payload);
    }
    strcpy(user->user.uuid, user_uuid);
    strcpy(user->user.name, body->user_name);
    TAILQ_INSERT_TAIL(&server->users, user, entries);
    server_event_user_logged_in(user_uuid);
    send_uuid(server, payload, user_uuid);
}

void s_server_event_logged_in(s_server_t *server,
    const p_payload_t *payload)
{
    s_user_t *user;
    login_t body;

    memcpy(&body, payload->data, sizeof(login_t));
    TAILQ_FOREACH(user, &server->users, entries) {
        if (strcmp(body.user_name, user->user.name) == 0) {
            server_event_user_logged_in(user->user.uuid);
            return send_uuid(server, payload, user->user.uuid);
        }
    }
    new_user(server, payload, &body);
}

void s_server_event_logged_out(s_server_t *server,
    const p_payload_t *payload)
{
    logout_t body;

    memcpy(&body, payload->data, sizeof(logout_t));
    server_event_user_logged_out(body.user_uuid);
    send_success(server, payload);
}

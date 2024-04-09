/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** logged
*/

#include <string.h>

#include "logging_server.h"
#include "server.h"
#include "unused.h"

void s_server_event_logged_in(UNUSED s_server_t *server,
    const p_payload_t *payload)
{
    login_t body;
    const char *user_uuid = get_uuid();

    memcpy(&body, payload->data, sizeof(login_t));
    server_event_user_logged_in(user_uuid);
}

void s_server_event_logged_out(UNUSED s_server_t *server,
    const p_payload_t *payload)
{
    logout_t body;

    memcpy(&body, payload->data, sizeof(logout_t));
    server_event_user_logged_out(body.user_uuid);
}

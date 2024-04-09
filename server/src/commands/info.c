/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** info
*/

#include <string.h>

#include "server.h"
#include "unused.h"

void s_server_event_get_user_info(UNUSED s_server_t *server,
    const p_payload_t *payload)
{
    user_info_t body;

    memcpy(&body, payload->data, sizeof(user_info_t));
}

void s_server_event_get_team_info(UNUSED s_server_t *server,
    const p_payload_t *payload)
{
    team_info_t body;

    memcpy(&body, payload->data, sizeof(team_info_t));
}

void s_server_event_get_channel_info(UNUSED s_server_t *server,
    const p_payload_t *payload)
{
    channel_info_t body;

    memcpy(&body, payload->data, sizeof(channel_info_t));
}

void s_server_event_get_thread_info(UNUSED s_server_t *server,
    const p_payload_t *payload)
{
    thread_info_t body;

    memcpy(&body, payload->data, sizeof(thread_info_t));
}

/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** list_teams
*/

#include "server.h"
#include "unused.h"

void s_server_event_list_teams(UNUSED s_server_t *server,
    const p_payload_t *payload)
{
    list_teams_t body;

    memcpy(&body, payload->data, sizeof(list_teams_t));
}

void s_server_event_list_channels(UNUSED s_server_t *server,
    const p_payload_t *payload)
{
    list_channels_t body;

    memcpy(&body, payload->data, sizeof(list_channels_t));
}

void s_server_event_list_threads(UNUSED s_server_t *server,
    const p_payload_t *payload)
{
    list_threads_t body;

    memcpy(&body, payload->data, sizeof(list_threads_t));
}

void s_server_event_list_replies(UNUSED s_server_t *server,
    const p_payload_t *payload)
{
    list_replies_t body;

    memcpy(&body, payload->data, sizeof(list_replies_t));
}

/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** list
*/

#include <string.h>

#include "server.h"
#include "unused.h"

void s_server_event_list_users(UNUSED s_server_t *server,
    UNUSED const p_payload_t *payload)
{}

void s_server_event_list_messages(UNUSED s_server_t *server,
    const p_payload_t *payload)
{
    list_messages_t body;

    memcpy(&body, payload->data, sizeof(list_messages_t));
}

void s_server_event_list_subscribed_users_in_team(UNUSED s_server_t *server,
    const p_payload_t *payload)
{
    list_subscribed_users_in_team_t body;

    memcpy(&body, payload->data, sizeof(list_subscribed_users_in_team_t));
}

void s_server_event_list_subscribed_teams(UNUSED s_server_t *server,
    const p_payload_t *payload)
{
    list_subscribed_teams_t body;

    memcpy(&body, payload->data, sizeof(list_subscribed_teams_t));
}

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

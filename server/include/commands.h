/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** event
*/

#ifndef COMMANDS_H
    #define COMMANDS_H

    #include "server.h"
    #include "event.h"

static struct {
    uint8_t event;
    void (*callback)(s_server_t *, const p_payload_t *);
} const events[] = {
    {EVT_LOGIN, &s_server_event_logged_in},
    {EVT_DISCONNECT, &s_server_event_logged_out},
    {EVT_LIST_USERS, &s_server_event_list_users},
    {EVT_SEND, &s_server_event_send_message},
    {EVT_LIST_MESSAGES, &s_server_event_list_messages},
    {EVT_SUBSCRIBE, &s_server_event_subscribe},
    {
        EVT_LIST_SUBSCRIBED_IN_TEAM,
        &s_server_event_list_subscribed_users_in_team
    },
    {EVT_LIST_SUBSCRIBED_TEAMS, &s_server_event_list_subscribed_teams},
    {EVT_UNSUBSCRIBE, &s_server_event_unsubscribe},
    {EVT_CREATE_TEAM, &s_server_event_team_created},
    {EVT_CREATE_CHANNEL, &s_server_event_channel_created},
    {EVT_CREATE_THREAD, &s_server_event_thread_created},
    {EVT_CREATE_REPLY, &s_server_event_reply_created},
    {EVT_LIST_TEAMS, &s_server_event_list_teams},
    {EVT_LIST_CHANNELS, &s_server_event_list_channels},
    {EVT_LIST_THREADS, &s_server_event_list_threads},
    {EVT_LIST_REPLIES, &s_server_event_list_replies},
    {EVT_INFO_USER, &s_server_event_get_user_info},
    {EVT_INFO_TEAM, &s_server_event_get_team_info},
    {EVT_INFO_CHANNEL, &s_server_event_get_channel_info},
    {EVT_INFO_THREAD, &s_server_event_get_thread_info},
    {EVT_PING, &s_server_event_ping},
};

#endif //COMMANDS_H

/*
** EPITECH PROJECT, 2024
** teams [WSL: Arch]
** File description:
** logger
*/

#ifndef LOGGER_H_
    #define LOGGER_H_

    #include "protocol.h"
    #include "client.h"
    #include "logging_client.h"
    #include "events.h"
    #include "events_structures.h"
    #include "unused.h"
    #include "logger2.h"
    #include "logger3.h"
    #include "logger_error.h"

    #include <string.h>
    #include <stdint.h>

    #define UNCOMBINED_EVT(evt, sub_evt) ((evt << 8) + sub_evt)

static inline void mt_log_client(const p_packet_t *payload, c_client_t *client)
{
    user_t user = {0};

    memcpy(&user, payload->data, sizeof(user_t));
    client->user = user;
    client_event_logged_in(user.uuid, user.name);
}

static inline void mt_logout_client(const p_packet_t *payload,
    c_client_t *client)
{
    user_t user = {0};

    memcpy(&user, payload->data, sizeof(user_t));
    client->user = user;
    client_event_logged_out(user.uuid, user.name);
    client->user = (user_t){0};
}

static inline void mt_receive_message(const p_packet_t *payload,
    UNUSED c_client_t *client)
{
    private_message_t message = {0};

    memcpy(&message, payload->data, sizeof(private_message_t));
    client_event_private_message_received(
        message.sender_uuid,
        message.body
    );
}

static inline void mt_thread_reply_received(const p_packet_t *payload,
    UNUSED c_client_t *client)
{
    reply_ref_t reply = {0};

    memcpy(&reply, payload->data, sizeof(reply_ref_t));
    client_event_thread_reply_received(
        reply.team_uuid,
        reply.thread_uuid,
        reply.user_uuid,
        reply.reply_body
    );
}

static inline void mt_team_created(const p_packet_t *payload,
    UNUSED c_client_t *client)
{
    team_t team = {0};

    memcpy(&team, payload->data, sizeof(team_t));
    client_event_team_created(
        team.uuid,
        team.name,
        team.description
    );
}

static inline void mt_channel_created(const p_packet_t *payload,
    UNUSED c_client_t *client)
{
    channel_t channel = {0};

    memcpy(&channel, payload->data, sizeof(channel_t));
    client_event_channel_created(
        channel.uuid,
        channel.name,
        channel.description
    );
}

static inline void mt_thread_created(const p_packet_t *payload,
    UNUSED c_client_t *client)
{
    thread_t thread = {0};

    memcpy(&thread, payload->data, sizeof(thread_t));
    client_event_thread_created(
        thread.uuid,
        thread.user_uuid,
        thread.timestamp,
        thread.title,
        thread.body
    );
}

static inline void mt_user_list(const p_packet_t *payload,
    UNUSED c_client_t *client)
{
    user_state_t user = {0};

    memcpy(&user, payload->data, sizeof(user_state_t));
    client_print_users(
        user.uuid,
        user.name,
        user.is_logged
    );
}

static inline void mt_team(const p_packet_t *payload,
    UNUSED c_client_t *client)
{
    team_t team = {0};

    memcpy(&team, payload->data, sizeof(team_t));
    client_print_teams(
        team.uuid,
        team.name,
        team.description
    );
}

static inline void mt_team_print_created(const p_packet_t *payload,
    UNUSED c_client_t *client)
{
    team_t team = {0};

    memcpy(&team, payload->data, sizeof(team_t));
    client_print_team_created(
        team.uuid,
        team.name,
        team.description
    );
}

static const struct {
    uint16_t type;
    void (*func)(const p_packet_t *payload, c_client_t *client);
} mt_logger[] = {
    {EVT_LOGIN, mt_log_client},
    {EVT_DISCONNECT, mt_logout_client},

    {EVT_LIST_USERS, mt_user_list},
    {UNCOMBINED_EVT(EVT_CONTINUE, EVT_LIST_USERS), mt_user_list},

    {EVT_LIST_MESSAGES, mt_private_message_list},
    {UNCOMBINED_EVT(EVT_CONTINUE, EVT_LIST_MESSAGES), mt_private_message_list},

    {EVT_SUBSCRIBE, mt_subscribe},

    {EVT_LIST_SUBSCRIBED_IN_TEAM, mt_user_list},
    {UNCOMBINED_EVT(EVT_CONTINUE, EVT_LIST_SUBSCRIBED_IN_TEAM), mt_user_list},

    {EVT_LIST_SUBSCRIBED_TEAMS, mt_team},
    {UNCOMBINED_EVT(EVT_CONTINUE, EVT_LIST_SUBSCRIBED_TEAMS), mt_team},

    {EVT_UNSUBSCRIBE, mt_unsubscribe},

    {EVT_CREATE_TEAM, mt_team_print_created},
    {EVT_CREATE_CHANNEL, mt_channel_print_created},
    {EVT_CREATE_THREAD, mt_thread_print_created},
    {EVT_CREATE_REPLY, mt_print_reply_created},

    {EVT_LIST_TEAMS, mt_team},
    {UNCOMBINED_EVT(EVT_CONTINUE, EVT_LIST_TEAMS), mt_team},

    {EVT_LIST_CHANNELS, mt_channel_list},
    {UNCOMBINED_EVT(EVT_CONTINUE, EVT_LIST_CHANNELS), mt_channel_list},

    {EVT_LIST_THREADS, mt_thread},
    {UNCOMBINED_EVT(EVT_CONTINUE, EVT_LIST_THREADS), mt_thread},

    {EVT_LIST_REPLIES, mt_reply_list},
    {UNCOMBINED_EVT(EVT_CONTINUE, EVT_LIST_REPLIES), mt_reply_list},

    {EVT_INFO_USER, mt_user_info},
    {EVT_INFO_TEAM, mt_team_info},
    {EVT_INFO_CHANNEL, mt_channel_info},
    {EVT_INFO_THREAD, mt_thread_info},

    {EVT_MESSAGE_RECEIVE, mt_receive_message},

    {EVT_REPLY_CREATE, mt_thread_reply_received},

    {EVT_TEAM_CREATE, mt_team_created},

    {EVT_CHANNEL_CREATE, mt_channel_created},

    {EVT_THREAD_CREATE, mt_thread_created},

    {EVT_ERROR_UNAUTHORIZED, mt_error_unauthorized},
    {EVT_ERROR_ALREADY, mt_already_exist},
    {EVT_ERROR_UNKNOWN_TEAM, mt_error_unknown_team},
    {EVT_ERROR_UNKNOWN_CHANNEL, mt_error_unknown_channel},
    {EVT_ERROR_UNKNOWN_THREAD, mt_error_unknown_thread},
    {EVT_ERROR_UNKNOWN_USER, mt_error_unknown_user},
    {INT16_MAX - 1, NULL}
};

#endif /* !LOGGER_H_ */

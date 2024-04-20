/*
** EPITECH PROJECT, 2024
** teams [WSL: Arch]
** File description:
** logger2
*/

#ifndef LOGGER2_H_
    #define LOGGER2_H_

    #include "protocol.h"
    #include "client.h"
    #include "logging_client.h"
    #include "events_structures.h"
    #include "unused.h"

    #include <string.h>

static inline void mt_subscribe(const p_packet_t *payload,
    UNUSED c_client_t *client)
{
    subscribe_t subscribe = {0};

    memcpy(&subscribe, payload->data, sizeof(subscribe_t));
    client_print_subscribed(
        subscribe.user_uuid,
        subscribe.team_uuid
    );
}

static inline void mt_unsubscribe(const p_packet_t *payload,
    UNUSED c_client_t *client)
{
    subscribe_t subscribe = {0};

    memcpy(&subscribe, payload->data, sizeof(subscribe_t));
    client_print_unsubscribed(
        subscribe.user_uuid,
        subscribe.team_uuid
    );
}

static inline void mt_channel_list(const p_packet_t *payload,
    UNUSED c_client_t *client)
{
    channel_t channel = {0};

    memcpy(&channel, payload->data, sizeof(channel_t));
    client_team_print_channels(
        channel.uuid,
        channel.name,
        channel.description
    );
}

static inline void mt_thread(const p_packet_t *payload,
    UNUSED c_client_t *client)
{
    thread_t thread = {0};

    memcpy(&thread, payload->data, sizeof(thread_t));
    client_channel_print_threads(
        thread.uuid,
        thread.user_uuid,
        thread.timestamp,
        thread.title,
        thread.body
    );
}

static inline void mt_reply_list(const p_packet_t *payload,
    UNUSED c_client_t *client)
{
    reply_t reply = {0};

    memcpy(&reply, payload->data, sizeof(reply_t));
    client_thread_print_replies(
        reply.thread_uuid,
        reply.user_uuid,
        reply.timestamp,
        reply.body
    );
}

static inline void mt_user_info(const p_packet_t *payload,
    UNUSED c_client_t *client)
{
    user_state_t user = {0};

    memcpy(&user, payload->data, sizeof(user_state_t));
    client_print_user(
        user.uuid,
        user.name,
        user.is_logged
    );
}

static inline void mt_private_message_list(const p_packet_t *payload,
    UNUSED c_client_t *client)
{
    private_message_t message = {0};

    memcpy(&message, payload->data, sizeof(private_message_t));
    client_private_message_print_messages(
        message.sender_uuid,
        message.timestamp,
        message.body
    );
}

static inline void mt_print_reply_created(const p_packet_t *payload,
    UNUSED c_client_t *client)
{
    reply_t reply = {0};

    memcpy(&reply, payload->data, sizeof(reply_t));
    client_print_reply_created(
        reply.thread_uuid,
        reply.user_uuid,
        reply.timestamp,
        reply.body
    );
}

static inline void mt_team_info(const p_packet_t *payload,
    UNUSED c_client_t *client)
{
    team_t team = {0};

    memcpy(&team, payload->data, sizeof(team_t));
    client_print_team(
        team.uuid,
        team.name,
        team.description
    );
}

#endif /* !LOGGER2_H_ */

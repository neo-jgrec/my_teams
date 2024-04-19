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

    #include <stdio.h>
    #include <string.h>

extern bool is_running;

static inline void mt_server_close(UNUSED const p_packet_t *payload,
    c_client_t *client)
{
    fprintf(stdout, "Server closed\n");
    is_running = false;
    client->user = (user_t){0};
}

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

static inline void mt_channel(const p_packet_t *payload,
    UNUSED c_client_t *client)
{
    channel_t channel = {0};

    memcpy(&channel, payload->data, sizeof(channel_t));
    client_print_channel_created(
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
    client_print_thread_created(
        thread.uuid,
        thread.user_uuid,
        thread.timestamp,
        thread.title,
        thread.body
    );
}

static inline void mt_reply(const p_packet_t *payload,
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

#endif /* !LOGGER2_H_ */

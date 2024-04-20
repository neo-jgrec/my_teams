/*
** EPITECH PROJECT, 2024
** teams [WSL: Arch]
** File description:
** logger3
*/

#ifndef LOGGER3_H_
    #define LOGGER3_H_
    #include "protocol.h"
    #include "client.h"
    #include "logging_client.h"
    #include "events_structures.h"
    #include "unused.h"

    #include <string.h>

static inline void mt_channel_info(const p_packet_t *payload,
    UNUSED c_client_t *client)
{
    channel_t channel = {0};

    memcpy(&channel, payload->data, sizeof(channel_t));
    client_print_channel(
        channel.uuid,
        channel.name,
        channel.description
    );
}

static inline void mt_thread_info(const p_packet_t *payload,
    UNUSED c_client_t *client)
{
    thread_t thread = {0};

    memcpy(&thread, payload->data, sizeof(thread_t));
    client_print_thread(
        thread.uuid,
        thread.user_uuid,
        thread.timestamp,
        thread.title,
        thread.body
    );
}

static inline void mt_channel_print_created(const p_packet_t *payload,
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

static inline void mt_thread_print_created(const p_packet_t *payload,
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

#endif /* !LOGGER3_H_ */

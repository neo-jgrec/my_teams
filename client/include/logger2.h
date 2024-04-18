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

#endif /* !LOGGER2_H_ */

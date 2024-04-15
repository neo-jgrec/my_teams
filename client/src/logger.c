/*
** EPITECH PROJECT, 2024
** teams [WSL: Arch]
** File description:
** logger
*/

#include "logging_client.h"
#include "protocol.h"
#include "events.h"

static void __mt_log_client(const p_payload_t *payload)
{
    // const user_t *user = (const user_t *)payload->data;
    // printf("User: %s\n", user->name);
}

void client_logger(const p_payload_t *payload)
{
    switch (payload->packet_type) {
        case EVT_LOGIN:
            __mt_log_client(payload);
            break;
        default:
            break;
    }
}

/*
** EPITECH PROJECT, 2024
** teams [WSL: Arch]
** File description:
** logger
*/

#include "logging_client.h"
#include "protocol.h"
#include "events.h"
#include "client.h"
#include "unused.h"

static void mt_log_client(UNUSED const p_payload_t *payload)
{
    printf("login\n");
}

void client_logger(const p_payload_t *payload)
{
    switch (payload->packet_type) {
    case EVT_LOGIN:
        mt_log_client(payload);
        break;
    case INT16_MAX - 1:
        printf("%s\n", payload->data);
        break;
    default:
        printf("no packet type? %d\n", payload->packet_type);
        break;
    }
}

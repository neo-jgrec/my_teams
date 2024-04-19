/*
** EPITECH PROJECT, 2024
** teams [WSL: Arch]
** File description:
** process
*/


#include "debug_print.h"
#include "client.h"

#include <stdlib.h>

void process_priority_queue(queue_head_t *queue, c_client_t *client)
{
    p_payload_t *payload;

    while (!TAILQ_EMPTY(&client->p_client->payloads)) {
        payload = TAILQ_FIRST(&client->p_client->payloads);
        client_logger(&payload->packet, client);
        TAILQ_REMOVE(&client->p_client->payloads, payload, entries);
        free(payload);
    }
}

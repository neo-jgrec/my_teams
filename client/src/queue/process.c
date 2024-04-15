/*
** EPITECH PROJECT, 2024
** teams [WSL: Arch]
** File description:
** process
*/

#include "client.h"

void process_priority_queue(queue_head_t *queue)
{
    queue_node_t *node;
    p_payload_t *payload;

    while (!TAILQ_EMPTY(queue)) {
        node = TAILQ_FIRST(queue);
        TAILQ_REMOVE(queue, node, entries);
        payload = node->payload;
        client_logger(payload);
        free(payload);
        free(node);
    }
}

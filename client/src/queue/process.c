/*
** EPITECH PROJECT, 2024
** teams [WSL: Arch]
** File description:
** process
*/

#include "client.h"

#include <stdint.h>
#include <stdlib.h>

void process_priority_queue(queue_head_t *queue)
{
    queue_node_t *node = NULL;

    while (!TAILQ_EMPTY(queue)) {
        node = TAILQ_FIRST(queue);
        client_logger(node->packet);
        TAILQ_REMOVE(queue, node, entries);
        node->packet->type = INT16_MAX;
        for (size_t i = 0; i < sizeof(node->packet->data); i++)
            node->packet->data[i] = 0;
        free(node);
    }
}

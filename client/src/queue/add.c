/*
** EPITECH PROJECT, 2024
** teams [WSL: Arch]
** File description:
** add
*/

#include "client.h"
#include "protocol.h"

#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

void add_to_priority_queue(p_packet_t *packet, queue_head_t *queue)
{
    queue_node_t *node = NULL;

    if (!packet)
        return;
    if (packet->type == INT16_MAX)
        return;
    node = malloc(sizeof(queue_node_t));
    node->packet = packet;
    if (node == NULL)
        return;
    TAILQ_INSERT_TAIL(queue, node, entries);
}

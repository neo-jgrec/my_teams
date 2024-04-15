/*
** EPITECH PROJECT, 2024
** teams [WSL: Arch]
** File description:
** add
*/

#include "client.h"
#include "protocol.h"

void add_to_priority_queue(p_payload_t *payload, queue_head_t *queue)
{
    queue_node_t *node = NULL;

    if (!payload || payload->packet_type == INT16_MAX)
        return;
    node = malloc(sizeof(queue_node_t));
    node->payload = p_create_payload(payload->packet_type, payload->data);
    if (node == NULL)
        return;
    TAILQ_INSERT_TAIL(queue, node, entries);
}

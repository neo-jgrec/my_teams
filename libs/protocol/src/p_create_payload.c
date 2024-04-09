/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** p_create_payload
*/

#include "protocol.h"

p_payload_t *p_create_payload(
    const uint8_t packet_type,
    const void *payload_data,
    const size_t payload_size
)
{
    p_payload_t *payload = calloc(1, sizeof(p_payload_t));

    if (!payload)
        return NULL;
    payload->packet.id = packet_type;
    payload->packet.size = payload_size;
    memcpy(payload->data, payload_data, payload_size);
    return payload;
}

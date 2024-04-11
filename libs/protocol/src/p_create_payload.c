/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** p_create_payload
*/

#include "protocol.h"

p_payload_t *p_create_payload(
    const uint8_t packet_type,
    const void *payload_data
)
{
    p_payload_t *payload = calloc(1, sizeof(p_payload_t));

    if (!payload)
        return NULL;
    payload->packet_type = packet_type;
    memcpy(payload->data, payload_data, DATA_SIZE);
    return payload;
}

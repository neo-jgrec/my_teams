/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** p_create_payload
*/

#include "../include/protocol.h"

p_payload_t *p_create_payload(
    uint8_t packet_type,
    const void *payload_data,
    size_t payload_size
)
{
    p_payload_t *payload = calloc(1, sizeof(p_payload_t));

    if (payload == NULL)
        return NULL;
    payload->packet.id = packet_type;
    payload->packet.size = payload_size;
    //payload->data = calloc(payload_size, sizeof(char));
    //if (payload->data == NULL) {
    //    free(payload);
    //    return NULL;
    //}
    memcpy(payload->data, payload_data, payload_size);
    return payload;
}

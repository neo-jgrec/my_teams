/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** p_create_payload
*/

#include "protocol.h"

p_payload_t *p_create_payload(
    const uint16_t packet_type,
    const void *payload_data
)
{
    p_payload_t *payload = calloc(1, sizeof(p_payload_t));
    uint16_t data_size = 0;

    if (!payload)
        return NULL;
    payload->packet_type = packet_type;
    if (payload_data) {
        data_size = strlen(payload_data) + 1;
        if (data_size <= DATA_SIZE) {
            memcpy(payload->data, payload_data, data_size);
        } else {
            free(payload);
            return NULL;
        }
    }

    return payload;
}

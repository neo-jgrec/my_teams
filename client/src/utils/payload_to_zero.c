/*
** EPITECH PROJECT, 2024
** teams [WSL: Arch]
** File description:
** payload_to_zero
*/

#include "protocol.h"

void payload_to_zero(p_payload_t *payload)
{
    payload->packet_type = INT16_MAX;
    memset(payload->data, 0, sizeof(payload->data));
}

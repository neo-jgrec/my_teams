/*
** EPITECH PROJECT, 2024
** teams [WSL: Arch]
** File description:
** payload_to_zero
*/

#include "protocol.h"

#include <stdint.h>
#include <string.h>

void packet_to_zero(p_packet_t *payload)
{
    payload->type = INT16_MAX;
    memset(payload->data, 0, sizeof(payload->data));
}

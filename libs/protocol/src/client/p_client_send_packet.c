/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** p_client_send_packet
*/

#include <string.h>
#include <unistd.h>

#include "protocol.h"

bool p_client_send_packet(const p_client_t *client, const uint16_t type,
    const void *data, const int size)
{
    p_packet_t packet = {type, {0}};

    memcpy(packet.data, data, size);
    return write(client->network_data.sockfd, &packet, sizeof(p_packet_t))
        != -1;
}

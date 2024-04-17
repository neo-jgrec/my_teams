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

    if (FD_ISSET(client->network_data.sockfd, &client->master_write_fds) == 0)
        return false;
    memcpy(packet.data, data, size);
    return write(client->network_data.sockfd, &packet, sizeof(p_packet_t))
        != -1;
}

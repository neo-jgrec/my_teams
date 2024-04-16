/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** p_client_listen
*/

#include <unistd.h>
#include <fcntl.h>

#include "protocol.h"

bool p_client_listen(const p_client_t *client, p_packet_t *packet)
{
    fcntl(client->network_data.sockfd, F_SETFL, O_NONBLOCK);
    return read(client->network_data.sockfd, packet, sizeof(p_packet_t)) > 0;
}

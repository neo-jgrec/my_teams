/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** p_server_send_packet
*/

#include <unistd.h>

#include "protocol.h"

bool p_server_send_packet(const p_packet_t *packet, const int client_fd,
    p_server_t *server)
{
    p_client_t *client;

    TAILQ_FOREACH(client, &server->clients, entries)
        if (client->network_data.sockfd == client_fd) {
            FD_SET(client->network_data.sockfd, &server->write_fds);
            break;
        }
    return client && write(client_fd, packet, sizeof(p_packet_t)) != -1;
}

bool p_server_send_packet_type(const uint16_t type, const int client_fd,
    p_server_t *server)
{
    const p_packet_t packet = {type, {0}};

    return p_server_send_packet(&packet, client_fd, server);
}

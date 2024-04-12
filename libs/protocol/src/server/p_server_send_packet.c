/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** p_server_send_packet
*/

#include "protocol.h"

bool p_server_send_packet(p_payload_t *payload, const int client_fd,
    p_server_t *server)
{
    p_client_t *client;

    if (!payload)
        return false;
    TAILQ_FOREACH(client, &server->clients, entries)
        if (client->network_data.sockfd == client_fd) {
            FD_SET(client->network_data.sockfd, &server->write_fds);
            break;
        }
    return client
        && write(client_fd, &payload->packet_type, sizeof(uint16_t)) != -1
        && write(client_fd, payload->data, DATA_SIZE) != -1;
}

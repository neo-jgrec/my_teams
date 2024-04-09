/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** p_server_send_packet
*/

#include "protocol.h"

// TODO: Free payload
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
    if (client && write(client_fd, &payload->packet, sizeof(p_packet_t)) != -1
        && write(client_fd, payload->data, DATA_SIZE) != -1)
        return false;
    return true;
}

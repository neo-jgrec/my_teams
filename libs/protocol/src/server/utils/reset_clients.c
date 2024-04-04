/*
** EPITECH PROJECT, 2024
** protocol
** File description:
** reset_clients
*/

#include "../../../include/protocol.h"

void reset_clients(p_server_t *server)
{
    p_client_t *current_client;

    FD_ZERO(&server->read_fds);
    FD_ZERO(&server->write_fds);
    FD_SET(server->network_data.sockfd, &server->read_fds);
    TAILQ_FOREACH(current_client, &server->clients, entries) {
        FD_SET(current_client->network_data.sockfd, &server->read_fds);
        FD_SET(current_client->network_data.sockfd, &server->write_fds);
    }
}

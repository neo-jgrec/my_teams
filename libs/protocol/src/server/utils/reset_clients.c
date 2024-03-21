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

    FD_ZERO(&server->set);
    FD_SET(server->network_data.sockfd, &server->set);
    TAILQ_FOREACH(current_client, &server->clients, entries) {
        FD_SET(current_client->network_data.sockfd, &server->set);
    }
}

/*
** EPITECH PROJECT, 2024
** protocol
** File description:
** new_client
*/

#include "protocol.h"

bool new_client(p_server_t *server)
{
    p_client_t *new_client = malloc(sizeof(p_client_t));
    if (!new_client)
        return false;
    socklen_t size = sizeof(new_client->network_data.server_addr);
    int new_socket = accept(
        server->network_data.sockfd,
        (struct sockaddr*)&new_client->network_data.server_addr,
        &size
    );
    if (new_socket < 0)
        return false;
    new_client->network_data.sockfd = new_socket;
    TAILQ_INSERT_TAIL(&server->clients, new_client, entries);
    FD_SET(new_socket, &server->master_read_fds);
    FD_SET(new_socket, &server->master_write_fds);
    return true;
}

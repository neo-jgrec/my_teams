/*
** EPITECH PROJECT, 2024
** protocol
** File description:
** server_socket
*/

#include "protocol.h"

p_server_t *server_socket(const int port)
{
    p_server_t *server = calloc(1, sizeof(p_server_t));

    if (!server)
        return NULL;
    server->network_data.sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (server->network_data.sockfd < 0) {
        free(server);
        return NULL;
    }
    server->network_data.server_addr = (struct sockaddr_in){
        AF_INET, htons(port), {INADDR_ANY}, {0}
    };
    FD_ZERO(&server->master_read_fds);
    FD_ZERO(&server->master_write_fds);
    FD_SET(server->network_data.sockfd, &server->master_read_fds);
    FD_SET(server->network_data.sockfd, &server->master_write_fds);
    return server;
}

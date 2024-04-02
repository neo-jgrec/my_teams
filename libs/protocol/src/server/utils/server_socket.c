/*
** EPITECH PROJECT, 2024
** protocol
** File description:
** server_socket
*/

#include "../../../include/protocol.h"
#include "../../../../../include/debug_print.h"

p_server_t *server_socket(int port)
{
    p_server_t *server = (p_server_t *)malloc(sizeof(p_server_t));

    server->network_data.sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (server->network_data.sockfd < 0) {
        DEBUG_PRINT("Socket creation failed: %s\n", strerror(errno));
        free(server);
        return NULL;
    }
    server->network_data.server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server->network_data.server_addr.sin_family = AF_INET;
    server->network_data.server_addr.sin_port = htons(port);
    return server;
}

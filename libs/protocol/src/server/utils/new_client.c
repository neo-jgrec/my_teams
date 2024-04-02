/*
** EPITECH PROJECT, 2024
** protocol
** File description:
** new_client
*/

#include "../../../include/protocol.h"
#include "../../../../../include/debug_print.h"

int new_client(p_server_t *server)
{
    p_client_t *new_client = malloc(sizeof(p_client_t));
    socklen_t size = sizeof(new_client->network_data.server_addr);
    int new_socket = accept(
        server->network_data.sockfd,
        (struct sockaddr *)&new_client->network_data.server_addr,
        &size
    );

    if (new_socket < 0) {
        DEBUG_PRINT("Accept failed: %s\n", strerror(errno));
        return -1;
    }
    new_client->network_data.sockfd = new_socket;
    DEBUG_PRINT("New client connected with sockfd %d\n", new_socket);
    TAILQ_INSERT_TAIL(&server->clients, new_client, entries);
    return 0;
}

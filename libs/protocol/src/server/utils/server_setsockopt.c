/*
** EPITECH PROJECT, 2024
** protocol
** File description:
** server_setsockopt
*/

#include "../../../include/protocol.h"

int server_setsockopt(p_server_t *server)
{
    if (setsockopt(
        server->network_data.sockfd, SOL_SOCKET, SO_REUSEADDR,
        &server->network_data.server_addr.sin_addr, sizeof(int)
    ) == -1) {
        perror("Setsockopt failed");
        close(server->network_data.sockfd);
        free(server);
        return -1;
    }
    return 0;
}

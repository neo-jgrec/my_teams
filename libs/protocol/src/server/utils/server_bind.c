/*
** EPITECH PROJECT, 2024
** protocol
** File description:
** server_bind
*/

#include <unistd.h>
#include <stdlib.h>

#include "protocol.h"

bool server_bind(p_server_t *server)
{
    if (bind(
        server->network_data.sockfd,
        (const struct sockaddr*)&server->network_data.server_addr,
        sizeof(server->network_data.server_addr)
    ) == -1) {
        close(server->network_data.sockfd);
        free(server);
        return false;
    }
    return true;
}

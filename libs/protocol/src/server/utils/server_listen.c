/*
** EPITECH PROJECT, 2024
** protocol
** File description:
** server_listen
*/

#include <unistd.h>
#include <stdlib.h>

#include "protocol.h"

bool server_listen(p_server_t *server)
{
    if (listen(server->network_data.sockfd, SOMAXCONN) == -1) {
        close(server->network_data.sockfd);
        free(server);
        return false;
    }
    return true;
}

/*
** EPITECH PROJECT, 2024
** protocol
** File description:
** server_listen
*/

#include "../../../include/protocol.h"
#include "../../../../../include/debug_print.h"

int server_listen(p_server_t *server)
{
    if (listen(server->network_data.sockfd, SOMAXCONN) == -1) {
        DEBUG_PRINT("Listen failed: %s\n", strerror(errno));
        close(server->network_data.sockfd);
        free(server);
        return -1;
    }
    return 0;
}

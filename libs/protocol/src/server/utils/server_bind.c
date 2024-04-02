/*
** EPITECH PROJECT, 2024
** protocol
** File description:
** server_bind
*/

#include "../../../include/protocol.h"
#include "../../../../../include/debug_print.h"

int server_bind(p_server_t *server)
{
    if (bind(
        server->network_data.sockfd,
        (const struct sockaddr *)&server->network_data.server_addr,
        sizeof(server->network_data.server_addr)
    ) == -1) {
        DEBUG_PRINT("Bind failed: %s\n", strerror(errno));
        close(server->network_data.sockfd);
        free(server);
        return -1;
    }
    return 0;
}

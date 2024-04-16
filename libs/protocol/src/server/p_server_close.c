/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** p_server_close
*/

#include "protocol.h"

void p_server_close(p_server_t *server)
{
    for (p_client_t *client = TAILQ_FIRST(&server->clients); client;
        client = TAILQ_FIRST(&server->clients)) {
        TAILQ_REMOVE(&server->clients, client, entries);
        close(client->network_data.sockfd);
        free(client);
    }
    close(server->network_data.sockfd);
    free(server);
}

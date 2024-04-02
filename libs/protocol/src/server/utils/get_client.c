/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** get_client
*/

#include "../include/protocol.h"

p_client_t *get_client(int fd, p_server_t *server)
{
    p_client_t *client;

    TAILQ_FOREACH(client, &server->clients, entries) {
        if (!client->sockfd)
            continue;
        if (client->sockfd == fd)
            break;
    }
    return NULL;
}

/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** get_client
*/

#include "protocol.h"

p_client_t *get_client(const int fd, const p_server_t *server)
{
    p_client_t *client;

    TAILQ_FOREACH(client, &server->clients, entries)
        if (client->sockfd && client->sockfd == fd)
            break;
    return NULL;
}

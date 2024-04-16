/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** p_client_create
*/

#include <arpa/inet.h>
#include <stdlib.h>

#include "protocol.h"

static p_client_t *client_socket(const char *ip, const int port)
{
    p_client_t *client = calloc(1, sizeof(p_client_t));

    client->network_data.sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (client->network_data.sockfd < 0) {
        free(client);
        return NULL;
    }
    client->network_data.server_addr.sin_addr.s_addr = inet_addr(ip);
    client->network_data.server_addr.sin_family = AF_INET;
    client->network_data.server_addr.sin_port = htons(port);
    return client;
}

static bool client_connect(p_client_t *client)
{
    if (connect(
        client->network_data.sockfd,
        (struct sockaddr*)&client->network_data.server_addr,
        sizeof(client->network_data.server_addr)
    ) < 0) {
        free(client);
        return false;
    }
    return true;
}

p_client_t *p_client_create(const char *ip, const int port)
{
    p_client_t *client = client_socket(ip, port);

    return client && client_connect(client) ? client : NULL;
}

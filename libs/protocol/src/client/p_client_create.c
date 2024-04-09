/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** p_client_create
*/

#include "protocol.h"
#include "debug_print.h"

static p_client_t *client_socket(const char *ip, int port)
{
    p_client_t *client = malloc(sizeof(p_client_t));

    client->network_data.sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (client->network_data.sockfd < 0) {
        DEBUG_PRINT("Socket creation failed: %s\n", strerror(errno));
        free(client);
        return NULL;
    }
    client->network_data.server_addr.sin_addr.s_addr = inet_addr(ip);
    client->network_data.server_addr.sin_family = AF_INET;
    client->network_data.server_addr.sin_port = htons(port);
    return client;
}

static int client_connect(p_client_t *client)
{
    if (connect(
        client->network_data.sockfd,
        (struct sockaddr*)&client->network_data.server_addr,
        sizeof(client->network_data.server_addr)
    ) < 0) {
        DEBUG_PRINT("Connection failed: %s\n", strerror(errno));
        free(client);
        return -1;
    }
    DEBUG_PRINT("Connected to server\n");
    return 0;
}

p_client_t *p_client_create(const char *ip, int port)
{
    p_client_t *client = client_socket(ip, port);

    if (client == NULL)
        return NULL;
    if (client_connect(client) == -1)
        return NULL;
    return client;
}

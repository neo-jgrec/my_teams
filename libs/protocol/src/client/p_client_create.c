/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** p_client_create
*/

#include "../include/protocol.h"

p_client_t *p_client_create(const char *ip, int port)
{
    p_client_t *client = (p_client_t *)malloc(sizeof(p_client_t));

    client->network_data.sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (client->network_data.sockfd < 0) {
        perror("Socket creation failed");
        free(client);
        return NULL;
    }
    client->network_data.server_addr.sin_family = AF_INET;
    client->network_data.server_addr.sin_port = htons(port);
    if (inet_pton(AF_INET, ip, &client->network_data.server_addr.sin_addr) <= 0) {
        perror("Invalid address/ Address not supported");
        free(client);
        return NULL;
    }
    if (connect(
        client->network_data.sockfd,
        (struct sockaddr *)&client->network_data.server_addr,
        sizeof(client->network_data.server_addr)
    ) < 0) {
        perror("Connection failed");
        free(client);
        return NULL;
    }
    printf("Connected to server\n");
    return client;
}
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
    int sockfd;
    struct sockaddr_in server_addr;

    if (!client) {
        perror("Memory allocation failed");
        return NULL;
    }
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        free(client);
        return NULL;
    }
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    if (inet_pton(AF_INET, ip, &server_addr.sin_addr) <= 0) {
        perror("Invalid address/ Address not supported");
        close(sockfd);
        free(client);
        return NULL;
    }
    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection failed");
        close(sockfd);
        free(client);
        return NULL;
    }
    client->network_data.sockfd = sockfd;
    client->network_data.server_addr = server_addr;
    return client;
}
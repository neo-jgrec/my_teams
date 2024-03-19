/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** p_server_create
*/

#include "../include/protocol.h"

p_server_t* p_server_create(int port)
{
    p_server_t* server = (p_server_t*)malloc(sizeof(p_server_t));
    int sockfd;
    struct sockaddr_in server_addr;

    if (!server) {
        perror("Memory allocation failed");
        return NULL;
    }
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        free(server);
        return NULL;
    }
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);
    if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        close(sockfd);
        free(server);
        return NULL;
    }
    TAILQ_INIT(&server->clients);
    server->network_data.sockfd = sockfd;
    server->network_data.server_addr = server_addr;
    listen(sockfd, SOMAXCONN);
    return server;
}
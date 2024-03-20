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
    server->network_data.sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (server->network_data.sockfd < 0) {
        perror("Socket creation failed");
        free(server);
        return NULL;
    }
    server->network_data.server_addr.sin_family = AF_INET;
    server->network_data.server_addr.sin_addr.s_addr = INADDR_ANY;
    server->network_data.server_addr.sin_port = htons(port);
    if(bind(
        server->network_data.sockfd,
        (const struct sockaddr *)&server->network_data.server_addr,
        sizeof(server->network_data.server_addr)
    ) == -1) {
        perror("Bind failed");
        close(server->network_data.sockfd);
        free(server);
        return NULL;
    }
    listen(server->network_data.sockfd, SOMAXCONN);
    TAILQ_INIT(&server->clients);
    return server;
}
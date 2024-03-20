/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** p_server_listen
*/

#include "../include/protocol.h"

p_payload_t* p_server_listen(p_server_t *server) {
    p_client_t *current_client;

    FD_ZERO(&server->set);
    FD_SET(server->network_data.sockfd, &server->set);
    TAILQ_FOREACH(current_client, &server->clients, entries) {
        FD_SET(current_client->network_data.sockfd, &server->set);
    }

    if (select(FD_SETSIZE, &server->set, NULL, NULL, NULL) == -1) {
        perror("Select failed");
        return NULL;
    }

    if (FD_ISSET(server->network_data.sockfd, &server->set)) {
        p_client_t *new_client = malloc(sizeof(p_client_t));
        socklen_t size = sizeof(new_client->network_data.server_addr);
        int new_socket = accept(
            server->network_data.sockfd,
            (struct sockaddr *)&new_client->network_data.server_addr,
            &size
        );
        if (new_socket < 0) {
            perror("Accept failed");
            return NULL;
        }
        new_client->network_data.sockfd = new_socket;
        printf("New client connected: %d\n", new_client->network_data.sockfd);
        TAILQ_INSERT_TAIL(&server->clients, new_client, entries);
    }

    for (int fd = 0; fd < FD_SETSIZE; fd++) {
        if (FD_ISSET(fd, &server->set)) {
            p_payload_t* payload = (p_payload_t*)malloc(sizeof(p_payload_t));
            if (payload == NULL) {
                perror("Memory allocation failed");
                return NULL;
            }
            if (recv(fd, &payload->packet, sizeof(payload->packet), 0) != sizeof(payload->packet)) {
                free(payload);
                return NULL;
            }
            payload->data = malloc(payload->packet.size);
            if (payload->data == NULL) {
                perror("Memory allocation failed");
                free(payload);
                return NULL;
            }
            if (recv(fd, payload->data, payload->packet.size, 0) != payload->packet.size) {
                free(payload->data);
                free(payload);
                return NULL;
            }

            return payload;
        }

    }
    return NULL;
}

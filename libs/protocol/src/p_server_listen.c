/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** p_server_listen
*/

#include "../include/protocol.h"

p_payload_t* p_server_listen(p_server_t *server) {
    FD_ZERO(&server->set);
    FD_SET(server->network_data.sockfd, &server->set);

    p_client_t *current_client, *tmp;
    TAILQ_FOREACH(current_client, &server->clients, entries) {
        tmp = TAILQ_NEXT(current_client, entries);
        if (FD_ISSET(current_client->network_data.sockfd, &server->set)) {
            // Handle client
        }
        current_client = tmp;
    }
}

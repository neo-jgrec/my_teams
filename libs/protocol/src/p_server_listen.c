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

    //TAILQ_FOREACH_SAFE(current_client, &server->clients, entries, tmp) {
    //    FD_SET(current_client->network_data.sockfd, &server->set);
    //}
}

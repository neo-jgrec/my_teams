/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** p_server_close
*/

#include "protocol.h"

void p_server_close(p_server_t *server)
{
    close(server->network_data.sockfd);
    server->network_data.sockfd = -1;
    free(server);
}

/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** p_client_close
*/

#include "protocol.h"

void p_client_close(p_client_t *client)
{
    close(client->network_data.sockfd);
    free(client);
}

/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** p_client_listen
*/

#include <unistd.h>
#include <string.h>
#include <fcntl.h>

#include "protocol.h"

bool p_client_listen(p_client_t *client, p_packet_t *packet)
{
    struct timeval tv = {0, 0};

    memcpy(&client->readfds, &client->master_read_fds, sizeof(fd_set));
    memcpy(&client->writefds, &client->master_write_fds, sizeof(fd_set));
    if (select(FD_SETSIZE, &client->readfds, &client->writefds, NULL, &tv)
        == -1)
        return false;
    if (!FD_ISSET(client->network_data.sockfd, &client->readfds))
        return false;
    return read(client->network_data.sockfd, packet, sizeof(p_packet_t)) > 0;
}

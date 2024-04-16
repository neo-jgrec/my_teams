/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** p_client_listen
*/

#include "protocol.h"
#include <fcntl.h>

bool p_client_listen(const p_client_t *client, p_payload_t *payload)
{
    const int fd = client->network_data.sockfd;

    fcntl(fd, F_SETFL, O_NONBLOCK);
    return payload
        && read(fd, &payload->packet_type, sizeof(uint16_t)) > 0
        && read(fd, payload->data, DATA_SIZE) > 0;
}

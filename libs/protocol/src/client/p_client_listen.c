/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** p_client_listen
*/

#include "protocol.h"

p_payload_t *p_client_listen(const p_client_t *client)
{
    p_payload_t *payload = calloc(1, sizeof(p_payload_t));
    const int fd = client->network_data.sockfd;

    if (payload && read(fd, &payload->packet, sizeof(p_packet_t))
        && read(fd, payload->data, payload->packet.size))
        return payload;
    free(payload);
    return NULL;
}

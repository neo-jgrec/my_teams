/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** p_client_listen
*/

#include "protocol.h"
#include <fcntl.h>

p_payload_t *p_client_listen(const p_client_t *client)
{
    p_payload_t *payload = calloc(1, sizeof(p_payload_t));
    const int fd = client->network_data.sockfd;

    if (payload) {
        fcntl(fd, F_SETFL, O_NONBLOCK);
        if (read(fd, &payload->packet_type, sizeof(uint16_t))
            && read(fd, payload->data, DATA_SIZE))
            return payload;
    }
    free(payload);
    return NULL;
}

/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** p_client_listen
*/

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "protocol.h"

static p_payload_t *receive_packet(const int fd)
{
    p_payload_t *payload = calloc(1, sizeof(p_payload_t));

    if (!payload)
        return NULL;
    if (read(fd, &payload->packet, sizeof(p_packet_t)) > 0) {
        write(fd, &payload->packet, sizeof(p_packet_t));
        return payload;
    }
    free(payload);
    return NULL;
}

p_payload_t *p_client_listen(p_client_t *client)
{
    struct timeval tv = {0, 0};

    TAILQ_INIT(&client->payloads);
    memcpy(&client->readfds, &client->master_read_fds, sizeof(fd_set));
    memcpy(&client->writefds, &client->master_write_fds, sizeof(fd_set));
    if (select(FD_SETSIZE, &client->readfds, &client->writefds, NULL,
        &tv) == -1)
        return NULL;
    for (int fd = 0; fd <= FD_SETSIZE; fd++) {
        if (FD_ISSET(fd, &client->readfds)) {

            if (fd == client->sockfd)
                continue;
            p_payload_t *payload = receive_packet(fd);

            if (!payload) {
                for (p_payload_t *tmp; !TAILQ_EMPTY(&client->payloads);) {
                    tmp = TAILQ_FIRST(&client->payloads);
                    TAILQ_REMOVE(&client->payloads, tmp, entries);
                    free(tmp);
                }
                return NULL;
            }
            payload->fd = fd;
            TAILQ_INSERT_TAIL(&client->payloads, payload, entries);
        }
    }
    return TAILQ_FIRST(&client->payloads);
}

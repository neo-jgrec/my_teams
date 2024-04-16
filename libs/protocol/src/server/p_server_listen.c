/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** p_server_listen
*/

#include <unistd.h>
#include <stdlib.h>

#include "protocol.h"

static p_payload_t *receive_packet(const int fd, const p_server_t *server)
{
    p_client_t *current_client;
    p_payload_t *payload = calloc(1, sizeof(p_payload_t));

    if (!payload)
        return NULL;
    TAILQ_FOREACH(current_client, &server->clients, entries) {
        if (current_client->network_data.sockfd != fd)
            continue;
        if (read(fd, &payload->packet, sizeof(p_packet_t)) > 0)
            return payload;
        break;
    }
    free(payload);
    return NULL;
}

static void server_listen_handle_payload(const int fd, p_server_t *server)
{
    p_client_t *client;
    p_payload_t *payload = receive_packet(fd, server);

    if (payload) {
        payload->fd = fd;
        TAILQ_INSERT_TAIL(&server->payloads, payload, entries);
        return;
    }
    FD_CLR(fd, &server->master_read_fds);
    FD_CLR(fd, &server->master_write_fds);
    TAILQ_FOREACH(client, &server->clients, entries)
        if (client->network_data.sockfd == fd) {
            TAILQ_REMOVE(&server->clients, client, entries);
            break;
        }
    free(client);
    close(fd);
}

p_payload_t *p_server_listen(p_server_t *server)
{
    TAILQ_INIT(&server->payloads);
    if (!select_server(server))
        return NULL;
    for (int fd = 0; fd < FD_SETSIZE; fd++) {
        if (!FD_ISSET(fd, &server->read_fds))
            continue;
        if (fd == server->network_data.sockfd)
            new_client(server);
        else
            server_listen_handle_payload(fd, server);
    }
    return TAILQ_FIRST(&server->payloads);
}

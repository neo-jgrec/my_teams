/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** p_server_listen
*/

#include "protocol.h"

static bool read_header(const int fd, p_payload_t *payload)
{
    return read(fd, &payload->packet_type, sizeof(uint8_t)) > 0;
}

static bool read_network_data(const int fd, p_payload_t *payload,
    const p_server_t *server)
{
    p_client_t *client;

    if (read(fd, &payload->network_data, sizeof(p_network_data_t)) <= 0)
        return false;
    TAILQ_FOREACH(client, &server->clients, entries)
        if (client->network_data.sockfd == fd)
            client->sockfd = payload->network_data.sockfd;
    return true;
}

static int read_body(const int fd, p_payload_t *payload)
{
    return read(fd, payload->data, DATA_SIZE) > 0;
}

static p_payload_t *receive_packet(const int fd, const p_server_t *server)
{
    p_payload_t *payload = calloc(1, sizeof(p_payload_t));
    p_client_t *current_client;

    if (!payload)
        return NULL;
    TAILQ_FOREACH(current_client, &server->clients, entries) {
        if (current_client->network_data.sockfd != fd)
            continue;
        if (!read_header(fd, payload)
            || !read_network_data(fd, payload, server)
            || !read_body(fd, payload)) {
            free(payload);
            return NULL;
        }
        return payload;
    }
    free(payload);
    return NULL;
}

static void server_listen_handle_payload(const int fd, p_server_t *server)
{
    p_client_t *client;
    p_payload_t *payload = receive_packet(fd, server);

    if (payload) {
        payload->client_fd = fd;
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

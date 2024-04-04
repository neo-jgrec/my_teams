/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** p_server_listen
*/

#include "../include/protocol.h"
#include "../../../include/debug_print.h"

static int read_header(int fd, p_payload_t *payload)
{
    size_t bytes_received = read(fd, &payload->packet, sizeof(p_packet_t));

    if (bytes_received <= 0) {
        DEBUG_PRINT("Packet header read failed: %s\n", strerror(errno));
        free(payload);
        return -1;
    }
    DEBUG_PRINT("Packet header received with id %d and size %d\n",
        payload->packet.id, payload->packet.size);
    return 0;
}

static int read_network_data(int fd, p_payload_t *payload, p_server_t *server)
{
    size_t bytes_received = read(fd, &payload->network_data,
        sizeof(p_network_data_t));
    p_client_t *client;

    if (bytes_received <= 0) {
        DEBUG_PRINT("Network data read failed: %s\n", strerror(errno));
        free(payload);
        return -1;
    }
    DEBUG_PRINT("Network data received with sockfd %d\n",
        payload->network_data.sockfd);
    TAILQ_FOREACH(client, &server->clients, entries) {
        if (client->network_data.sockfd == fd)
            client->sockfd = payload->network_data.sockfd;
    }
    return 0;
}

static int read_body(int fd, p_payload_t *payload)
{
    size_t bytes_received = read(fd, payload->data, payload->packet.size);

    if (bytes_received <= 0) {
        DEBUG_PRINT("Packet body read failed: %s\n", strerror(errno));
        free(payload);
        return -1;
    }
    DEBUG_PRINT("Packet body received with size %d\n", payload->packet.size);
    return 0;
}

static p_payload_t *receive_packet(int fd, p_server_t *server)
{
    p_payload_t *payload = calloc(1, sizeof(p_payload_t));
    p_client_t *current_client;

    if (!payload) {
        DEBUG_PRINT("Malloc failed: %s\n", strerror(errno));
        return NULL;
    }
    TAILQ_FOREACH(current_client, &server->clients, entries) {
        if (current_client->network_data.sockfd != fd)
            continue;
        if (read_header(fd, payload) == -1)
            return NULL;
        if (read_network_data(fd, payload, server) == -1)
            return NULL;
        memset(payload->data, 0, DATA_SIZE);
        if (read_body(fd, payload) == -1)
            return NULL;
        return payload;
    }
    return NULL;
}

p_payload_t *p_server_listen(p_server_t *server)
{
    p_client_t *current_client;

    reset_clients(server);
    if (select_server(server) == -1)
        return NULL;
    if (FD_ISSET(server->network_data.sockfd, &server->read_fds))
        if (new_client(server) == -1)
            return NULL;
    for (int fd = 0; fd < FD_SETSIZE; fd++)
        if (FD_ISSET(fd, &server->read_fds))
            return receive_packet(fd, server);
    TAILQ_FOREACH(current_client, &server->clients, entries)
        if (FD_ISSET(
            current_client->network_data.sockfd,
            &server->write_fds
        )) {
            FD_CLR(current_client->network_data.sockfd, &server->write_fds);
            return NULL;
        }
    return NULL;
}

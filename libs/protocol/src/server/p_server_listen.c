/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** p_server_listen
*/

#include "../include/protocol.h"
#include "../../../include/debug_print.h"

//static char *get_buffer(int fd)
//{
//    int read_size;
//    char *buffer = calloc(1024, sizeof(char));
//
//    if (buffer == NULL) {
//        perror("Calloc failed");
//        return NULL;
//    }
//    read_size = read(fd, buffer, 1024);
//    if (read_size == -1) {
//        perror("Read failed");
//        return NULL;
//    }
//    buffer[read_size] = '\0';
//    return buffer;
//}

static int read_header(int fd, p_payload_t *payload)
{
    size_t bytes_received = read(fd, &payload->packet, sizeof(p_packet_t));

    if (bytes_received == (size_t)-1) {
        perror("Header read failed");
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

    if (bytes_received == (size_t)-1) {
        perror("Network data read failed");
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

    if (bytes_received == (size_t)-1) {
        perror("Payload data read failed");
        free(payload->data);
        free(payload);
        return -1;
    }
    DEBUG_PRINT("Packet body received with size %d\n", payload->packet.size);
    return 0;
}

static p_payload_t *receive_packet(int fd, p_server_t *server)
{
    p_payload_t *payload = (p_payload_t *)malloc(sizeof(p_payload_t));

    if (!payload) {
        perror("Malloc failed");
        return NULL;
    }
    if (read_header(fd, payload) == -1)
        return NULL;
    if (read_network_data(fd, payload, server) == -1)
        return NULL;
    payload->data = malloc(payload->packet.size);
    if (payload->data == NULL) {
        perror("Malloc failed");
        free(payload);
        return NULL;
    }
    if (read_body(fd, payload) == -1)
        return NULL;
    return payload;
}

p_payload_t *p_server_listen(p_server_t *server)
{
    reset_clients(server);
    if (select_server(server) == -1)
        return NULL;
    if (FD_ISSET(server->network_data.sockfd, &server->set))
        if (new_client(server) == -1)
            return NULL;
    for (int fd = 0; fd < FD_SETSIZE; fd++)
        if (FD_ISSET(fd, &server->set))
            return receive_packet(fd, server);
    return NULL;
}

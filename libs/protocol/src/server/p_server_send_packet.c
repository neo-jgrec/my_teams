/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** p_server_send_packet
*/

#include "../include/protocol.h"
#include "../../../include/debug_print.h"

static int p_server_send_packet_header(
    p_payload_t *payload,
    int client_fd
)
{
    size_t size = write(
        client_fd,
        &payload->packet,
        sizeof(p_packet_t)
    );

    if (size == (size_t)-1) {
        DEBUG_PRINT("Packet header write failed: %s\n", strerror(errno));
        return -1;
    }
    DEBUG_PRINT("Packet header sent with id %d and size %d\n",
        payload->packet.id, payload->packet.size);
    return 0;
}

static int p_server_send_packet_body(
    p_payload_t *payload,
    int client_fd
)
{
    size_t size = write(
        client_fd,
        payload->data,
        payload->packet.size
    );

    if (size == (size_t)-1) {
        DEBUG_PRINT("Packet body write failed: %s\n", strerror(errno));
        return -1;
    }
    printf("Packet body sent with size %d\n", payload->packet.size);
    DEBUG_PRINT("Packet body sent with size %d\n", payload->packet.size);
    return 0;
}

int p_server_send_packet(
    p_payload_t *payload,
    int client_fd,
    p_server_t *server
)
{
    p_client_t *client;

    if (payload == NULL)
        return -1;
    TAILQ_FOREACH(client, &server->clients, entries) {
        if (client->sockfd == client_fd)
            break;
    }
    if (p_server_send_packet_header(payload,
        client->network_data.sockfd) == -1)
        return -1;
    if (p_server_send_packet_body(payload, client->network_data.sockfd) == -1)
        return -1;
    free(payload->data);
    free(payload);
    return 0;
}

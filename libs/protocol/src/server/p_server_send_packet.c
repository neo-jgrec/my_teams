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
        &(payload->packet),
        sizeof(p_packet_t)
    );

    if (size == (size_t)-1) {
        perror("Header write failed");
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
        perror("Payload data write failed");
        return -1;
    }
    printf("Packet body sent with size %d\n", payload->packet.size);
    DEBUG_PRINT("Packet body sent with size %d\n", payload->packet.size);
    return 0;
}

static int close_client_connection(int client_fd)
{
    if (close(client_fd) == -1) {
        perror("Client connection close failed");
        return -1;
    }
    return 0;
}

int p_server_send_packet(
    uint8_t packet_type,
    const void *payload_data,
    size_t payload_size,
    int client_fd
)
{
    p_payload_t *payload = p_create_payload(
        packet_type, payload_data, payload_size
    );

    if (payload == NULL)
        return -1;
    if (p_server_send_packet_header(payload, client_fd) == -1)
        return -1;
    if (p_server_send_packet_body(payload, client_fd) == -1)
        return -1;
    free(payload->data);
    free(payload);
    if (close_client_connection(client_fd) == -1)
        return -1;
    return 0;
}

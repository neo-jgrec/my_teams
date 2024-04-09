/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** p_client_send_packet
*/

#include "../../../../include/debug_print.h"
#include "protocol.h"

static int p_client_send_packet_header(
    p_client_t *client,
    p_payload_t *payload
)
{
    size_t size = write(
        client->network_data.sockfd,
        &(payload->packet),
        sizeof(p_packet_t)
    );

    if (size == (size_t)-1) {
        DEBUG_PRINT("Header write failed: %s\n", strerror(errno));
        return -1;
    }
    DEBUG_PRINT("Packet header sent with id %d and size %d\n",
        payload->packet.id, payload->packet.size);
    return 0;
}

static int p_client_send_packet_network_data(
    p_client_t *client,
    p_payload_t *payload
)
{
    size_t size = write(
        client->network_data.sockfd,
        &(payload->network_data),
        sizeof(p_network_data_t)
    );

    if (size == (size_t)-1) {
        DEBUG_PRINT("Network data write failed: %s\n", strerror(errno));
        return -1;
    }
    DEBUG_PRINT("Network data sent with sockfd %d\n",
        payload->network_data.sockfd);
    return 0;
}

static int p_client_send_packet_body(
    p_client_t *client,
    p_payload_t *payload
)
{
    size_t size = write(
        client->network_data.sockfd,
        payload->data,
        payload->packet.size
    );

    if (size == (size_t)-1) {
        DEBUG_PRINT("Payload data write failed: %s\n", strerror(errno));
        return -1;
    }
    DEBUG_PRINT("Packet body sent with size %d\n", payload->packet.size);
    return 0;
}

int p_client_send_packet(
    uint8_t packet_type,
    const void *payload_data,
    size_t payload_size,
    p_client_t *client
)
{
    p_payload_t *payload = p_create_payload(
        packet_type, payload_data, payload_size
    );

    payload->network_data = client->network_data;
    if (client == NULL || payload == NULL || payload->packet.size == 0)
        return -1;
    if (p_client_send_packet_header(client, payload) == -1)
        return -1;
    if (p_client_send_packet_network_data(client, payload) == -1)
        return -1;
    if (p_client_send_packet_body(client, payload) == -1)
        return -1;
    memset(payload->data, 0, DATA_SIZE);
    free(payload);
    return 0;
}

/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** p_client_send_packet
*/

#include "protocol.h"

static bool p_client_send_packet_type(const p_client_t *client,
    const p_payload_t *payload)
{
    return write(
        client->network_data.sockfd,
        &(payload->packet_type),
        sizeof(uint8_t)
    ) != -1;
}

static bool p_client_send_packet_network_data(const p_client_t *client,
    const p_payload_t *payload)
{
    return write(
        client->network_data.sockfd,
        &(payload->network_data),
        sizeof(p_network_data_t)
    ) != -1;
}

static bool p_client_send_packet_body(const p_client_t *client,
    const p_payload_t *payload)
{
    return write(
        client->network_data.sockfd,
        payload->data,
        DATA_SIZE
    ) != -1;
}

int p_client_send_packet(
    const uint8_t packet_type,
    const void *payload_data,
    const p_client_t *client
)
{
    p_payload_t *payload = p_create_payload(packet_type, payload_data);

    payload->network_data = client->network_data;
    return client && payload
        && p_client_send_packet_type(client, payload)
        && p_client_send_packet_network_data(client, payload)
        && p_client_send_packet_body(client, payload) ? 0 : -1;
}

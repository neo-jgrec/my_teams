/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** p_server_send_packet
*/

#include "protocol.h"

static bool p_server_send_packet_header(
    const p_payload_t *payload,
    const int client_fd
)
{
    return write(
        client_fd,
        &payload->packet,
        sizeof(p_packet_t)
    ) != -1;
}

static bool p_server_send_packet_body(
    const p_payload_t *payload,
    const int client_fd
)
{
    return write(
        client_fd,
        payload->data,
        payload->packet.size
    ) != -1;
}

bool p_server_send_packet(
    p_payload_t *payload,
    const int client_fd,
    p_server_t *server
)
{
    p_client_t *client;

    if (!payload)
        return false;
    TAILQ_FOREACH(client, &server->clients, entries)
        if (client->sockfd == client_fd) {
            FD_SET(client->network_data.sockfd, &server->write_fds);
            break;
        }
    if (!client
        || !p_server_send_packet_header(payload, client->network_data.sockfd)
        || !p_server_send_packet_body(payload, client->network_data.sockfd))
        return false;
    memset(payload->data, 0, DATA_SIZE);
    free(payload);
    return true;
}

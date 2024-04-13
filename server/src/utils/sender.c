/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** basic
*/

#include "protocol.h"
#include "server.h"
#include "events.h"

void send_event(const s_server_t *server, const p_payload_t *payload,
    const event_t type)
{
    p_payload_t response = {0};

    response.packet_type = type;
    p_server_send_packet(&response, payload->client_fd, server->socket);
}

void send_event_body(const s_server_t *server, const p_payload_t *payload,
    const void *body, const event_t type)
{
    p_payload_t response = {0};

    response.packet_type = type;
    memcpy(response.data, body, sizeof(body));
    p_server_send_packet(&response, payload->client_fd, server->socket);
}

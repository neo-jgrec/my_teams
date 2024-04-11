/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** basic
*/

#include "protocol.h"
#include "server.h"
#include "event.h"

void send_success(const s_server_t *server, const p_payload_t *payload)
{
    p_payload_t response = {0};

    response.packet_type = EVT_SUCCESS;
    p_server_send_packet(&response, payload->client_fd, server->socket);
}

void send_error(const s_server_t *server, const p_payload_t *payload)
{
    p_payload_t response = {0};

    response.packet_type = EVT_ERROR;
    p_server_send_packet(&response, payload->client_fd, server->socket);
}

void send_uuid(const s_server_t *server, const p_payload_t *payload,
    const char *uuid)
{
    p_payload_t response = {0};

    response.packet_type = EVT_SUCCESS;
    memcpy(response.data, uuid, UUID_LENGTH);
    p_server_send_packet(&response, payload->client_fd, server->socket);
}

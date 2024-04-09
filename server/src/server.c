/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** server
*/

#include <stdlib.h>

#include "protocol.h"
#include "commands.h"
#include "event.h"

void server(const char *str_port)
{
    const int port = atoi(str_port);
    s_server_t server = {};
    p_server_t *server_socket;
    p_payload_t *payload;

    if (port < 1024 || port > 65535)
        exit(EXIT_FAILURE);
    server_socket = p_server_create(port);
    if (!server_socket)
        exit(EXIT_FAILURE);
    while (p_server_is_open()) {
        payload = p_server_listen(server_socket);
        if (!payload)
            continue;
        for (payload = TAILQ_FIRST(&server_socket->payloads); payload; payload =
             TAILQ_FIRST(&server_socket->payloads)) {
            TAILQ_REMOVE(&server_socket->payloads, payload, entries);
            if (payload->packet_type < NB_EVT)
                events[payload->packet_type].callback(&server, payload);
            free(payload);
        }
    }
    p_server_close(server_socket);
}

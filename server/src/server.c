/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** server
*/

#include <stdlib.h>

#include "protocol.h"
#include "commands.h"
#include "events.h"

static void s_listen(s_server_t server)
{
    p_payload_t *payload = p_server_listen(server.socket);

    if (!payload)
        return;
    for (payload = TAILQ_FIRST(&server.socket->payloads); payload; payload =
         TAILQ_FIRST(&server.socket->payloads)) {
        TAILQ_REMOVE(&server.socket->payloads, payload, entries);
        if (payload->packet_type < NB_EVT)
            events[payload->packet_type].callback(&server, payload);
        free(payload);
    }
}

void server(const char *str_port)
{
    const int port = atoi(str_port);
    s_server_t server = {0};

    if (port < 1024 || port > 65535)
        exit(EXIT_FAILURE);
    printf("Server started on port %d\n", port);
    server.socket = p_server_create(port);
    if (!server.socket)
        exit(EXIT_FAILURE);
    while (p_server_is_open())
        s_listen(server);
    p_server_close(server.socket);
    printf("Server closed\n");
}

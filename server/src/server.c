/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** server
*/

#include <stdlib.h>
#include <stdio.h>

#include "protocol.h"
#include "commands.h"
#include "events.h"

static void s_listen(s_server_t *server)
{
    p_payload_t *payload = p_server_listen(server->socket);

    if (!payload)
        return;
    for (payload = TAILQ_FIRST(&server->socket->payloads); payload; payload =
        TAILQ_FIRST(&server->socket->payloads)) {
        TAILQ_REMOVE(&server->socket->payloads, payload, entries);
        if (payload->packet.type < NB_EVT)
            events[payload->packet.type].callback(server, payload);
        free(payload);
    }
}

static void init_list(s_server_t *server)
{
    TAILQ_INIT(&server->users);
    TAILQ_INIT(&server->teams);
    TAILQ_INIT(&server->channels);
    TAILQ_INIT(&server->threads);
    TAILQ_INIT(&server->replies);
    TAILQ_INIT(&server->private_messages);
    TAILQ_INIT(&server->subscribes);
    TAILQ_INIT(&server->logged);
    load(server);
}

void server(const char *str_port)
{
    const int port = atoi(str_port);
    s_server_t server = {0};

    if (port < 1024 || port > 65535) {
        printf("Invalid port\n");
        exit(EXIT_FAILURE);
    }
    printf("Server started on port %d\n", port);
    server.socket = p_server_create(port);
    if (!server.socket) {
        printf("Server creation failed\n");
        exit(EXIT_FAILURE);
    }
    init_list(&server);
    while (p_server_is_open())
        s_listen(&server);
    p_server_close(server.socket);
    save(&server);
    printf("Server closed\n");
}

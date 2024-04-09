/*
** EPITECH PROJECT, 2024
** my_teams [WSL: Arch]
** File description:
** main
*/

#include <stdio.h>

#include "protocol.h"
#include "protocol_client.h"
#include "protocol_server.h"

int main(void)
{
    const int port = 1235;

    printf("[SERVER] Opening server on port %i\n", port);
    p_server_t *server = p_server_create(port);
    if (!server) {
        fprintf(stderr, "[SERVER] Server creation failed\n");
        return EXIT_FAILURE;
    }
    printf("[SERVER] Server created\n\n");

    p_payload_t *payload_resp = p_create_payload(
        EVTS_SUCCESS, "Tamere\n"
    );

    while (p_server_is_open()) {
        p_payload_t *payload = p_server_listen(server);
        if (!payload)
            continue;
        TAILQ_FOREACH(payload, &server->payloads, entries) {
            printf("[SERVER] Received packet of type: %d\n",
                payload->packet_type);
            printf("[SERVER] Received payload: %s\n", (char*)payload->data);
            printf("[SERVER] Received from client: %d\n\n", payload->client_fd);
            if (payload->packet_type == EVTC_LOGIN)
                p_server_send_packet(payload_resp, payload->client_fd, server);
        }
    }
    p_server_close(server);
    printf("[SERVER] Server closed\n");
    return EXIT_SUCCESS;
}

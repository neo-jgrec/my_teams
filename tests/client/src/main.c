/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** main
*/

#include <stdio.h>
#include <stdlib.h>

#include "protocol.h"
#include "events.h"

#define MAX_NAME_LENGTH 32

int main(void)
{
    const char ip[] = "127.0.0.1";
    const int port = 1235;
    bool is_running = true;

    printf("[CLIENT] Opening client on %s:%i\n", ip, port);
    p_client_t *client = p_client_create(ip, port);
    if (!client) {
        fprintf(stderr, "[CLIENT] Client creation failed\n\n");
        return EXIT_FAILURE;
    }
    printf("[CLIENT] Client created\n\n");

    printf("[CLIENT] Sent login packet\n\n");
    p_client_send_packet(EVTC_LOGIN, "Hello", client);
    while (is_running) {
        p_payload_t *payload = p_client_listen(client);
        if (!payload)
            continue;
        printf("[CLIENT] Received packet of type %d\n", payload->packet_type);
        printf("[CLIENT] Received payload: %s\n", (char*)payload->data);
        printf("[CLIENT] Received from client %d\n\n",
            payload->network_data.sockfd);
        free(payload);
        //is_running = false;
    }
    p_client_close(client);
    return EXIT_SUCCESS;
}

/*
** EPITECH PROJECT, 2024
** my_teams [WSL: Arch]
** File description:
** main
*/

#include <stdio.h>
#include "../../../include/debug_print.h"
#include "../../../libs/protocol/include/protocol.h"
#include "../../../libs/protocol/include/protocol_client.h"
#include "../../../libs/protocol/include/protocol_server.h"

int main(void)
{
    printf("Super le server !\n");
    DEBUG_PRINT("Super debug du %d\n", 42);

    p_server_t* server = p_server_create(1235);
    if (!server) {
        fprintf(stderr, "Server creation failed\n");
        return 1;
    }

    p_payload_t *payload_resp = p_create_payload(
        EVT_SUCCES, "Tamere\n", 8
    );

    while (1) {
        p_payload_t *payload = p_server_listen(server);
        if (payload) {
            printf("Received packet of type %d\n", payload->packet.id);
            printf("Received payload of size %d\n", payload->packet.size);
            printf("Received payload: %s\n", (char*)payload->data);
            printf("Received from client %d\n\n", payload->network_data.sockfd);
            printf("Received from client2 %d\n\n", payload->client_fd);
            if (payload->packet.id == EVT_LOGIN)
                p_server_send_packet(payload_resp, payload->client_fd, server);
            free(payload);
        }
    }

    close(server->network_data.sockfd);
    free(server);

    return 0;
}

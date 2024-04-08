/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** main
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/client.h"
#include "../../../libs/protocol/include/protocol.h"
#include "../../../libs/protocol/include/protocol_client.h"
#include "../../../libs/protocol/include/protocol_server.h"
#include "../../../include/debug_print.h"

#define MAX_NAME_LENGTH 32



int main(void)
{
    p_client_t* client = p_client_create("127.0.0.1", 1235);
    if (!client) {
        fprintf(stderr, "Client creation failed\n");
        return 1;
    }

    p_client_send_packet(EVT_LOGIN, "Hello", 6, client);
    printf("Sent login packet\n");
    while (1) {
        p_payload_t *payload = p_client_listen(client);
        if (payload) {
            printf("Received packet of type %d\n", payload->packet.id);
            printf("Received payload of size %d\n", payload->packet.size);
            printf("Received payload: %s\n", (char*)payload->data);
            printf("Received from client %d\n\n", payload->network_data.sockfd);
            free(payload);
        }
    }

    close(client->network_data.sockfd);
    free(client);
    return 0;
}

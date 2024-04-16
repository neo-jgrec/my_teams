/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** main
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "protocol.h"
#include "events.h"

#define MAX_NAME_LENGTH 32

int main(void)
{
    const char ip[] = "127.0.0.1";
    const int port = 1235;

    printf("[CLIENT] Opening client on %s:%i\n", ip, port);
    p_client_t *client = p_client_create(ip, port);
    if (!client) {
        fprintf(stderr, "[CLIENT] Client creation failed\n\n");
        return EXIT_FAILURE;
    }
    printf("[CLIENT] Client created\n\n");

    printf("[CLIENT] Sent login packet\n\n");
    p_client_send_packet(client, EVT_LOGIN, "Batman", 6);

    p_packet_t packet = {0};
    while (!p_client_listen(client, &packet));

    printf("[CLIENT] Received packet of type %d\n", packet.type);
    printf("[CLIENT] Received payload: [");
    fflush(stdout);
    write(1, packet.data, DATA_SIZE);
    printf("]\n");

    p_client_close(client);
    return EXIT_SUCCESS;
}

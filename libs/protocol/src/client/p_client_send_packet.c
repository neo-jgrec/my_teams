/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** p_client_send_packet
*/

#include "../include/protocol.h"

int p_client_send_packet(
    uint8_t packet_type,
    const void *payload_data,
    size_t payload_size,
    p_client_t *client
) {
    p_packet_t packet;

    if (client == NULL) {
        fprintf(stderr, "Invalid client\n");
        return -1;
    }
    packet.size = htons(payload_size + sizeof(packet_type));
    packet.id = packet_type;
    if (send(client->network_data.sockfd, &packet, sizeof(packet), 0) != sizeof(packet)) {
        perror("Packet sending failed");
        return -1;
    }
    if (send(client->network_data.sockfd, payload_data, payload_size, 0) != (ssize_t)payload_size) {
        perror("Payload sending failed");
        return -1;
    }
    printf("Packet sent\n");
    printf("Packet type: %d\n", packet_type);
    printf("Payload size: %ld\n", payload_size);
    printf("Payload: %s\n", (char*)payload_data);
    printf("Client socket: %d\n", client->network_data.sockfd);
    return 0;
}
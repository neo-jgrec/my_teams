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

    packet.size = sizeof(packet) + payload_size;
    packet.id = packet_type;
    if (send(client->network_data.sockfd, &packet, sizeof(packet), 0) < 0) {
        perror("Send failed");
        return -1;
    }
    if (send(client->network_data.sockfd, payload_data, payload_size, 0) < 0) {
        perror("Send failed");
        return -1;
    }
    return 0;
}
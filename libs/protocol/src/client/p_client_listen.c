/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** p_client_listen
*/

#include "../include/protocol.h"

p_payload_t* p_client_listen(p_client_t *client) {
    p_payload_t *payload = (p_payload_t*)malloc(sizeof(p_payload_t));
    int sockfd = client->network_data.sockfd;
    p_packet_t packet;

    if (!payload) {
        perror("Memory allocation failed");
        return NULL;
    }
    if (recv(sockfd, &packet, sizeof(packet), 0) < 0) {
        perror("Receive failed");
        free(payload);
        return NULL;
    }
    payload->data = malloc(packet.size);
    if (!payload->data) {
        perror("Memory allocation failed");
        free(payload);
        return NULL;
    }
    if (recv(sockfd, payload->data, packet.size, 0) < 0) {
        perror("Receive failed");
        free(payload->data);
        free(payload);
        return NULL;
    }
    payload->packet = packet;
    return payload;
}

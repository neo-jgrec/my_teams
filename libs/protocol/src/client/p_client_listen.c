/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** p_client_listen
*/

#include "protocol.h"
#include "debug_print.h"

static int read_header(int fd, p_payload_t* payload)
{
    size_t size = read(fd, &(payload->packet), sizeof(p_packet_t));

    if (size == (size_t)-1) {
        DEBUG_PRINT("Header read failed: %s\n", strerror(errno));
        return -1;
    }
    DEBUG_PRINT("Packet header received with id %d and size %d\n",
                payload->packet.id, payload->packet.size);
    return 0;
}

static int read_body(int fd, p_payload_t* payload)
{
    size_t size = read(fd, payload->data, payload->packet.size);

    if (size == (size_t)-1) {
        DEBUG_PRINT("Body read failed: %s\n", strerror(errno));
        return -1;
    }
    DEBUG_PRINT("Packet body received with size %d\n", payload->packet.size);
    return 0;
}

p_payload_t* p_client_listen(p_client_t* client)
{
    p_payload_t* payload = malloc(sizeof(p_payload_t));

    if (!payload) {
        DEBUG_PRINT("Malloc failed: %s\n", strerror(errno));
        return NULL;
    }
    if (read_header(client->network_data.sockfd, payload) == -1)
        return NULL;
    memset(payload->data, 0, DATA_SIZE);
    if (read_body(client->network_data.sockfd, payload) == -1)
        return NULL;
    return payload;
}

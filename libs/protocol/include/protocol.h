/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** protocol
*/

#ifndef PROTOCOL_H_
    #define PROTOCOL_H_

    #include <stdio.h>
    #include <stdint.h>
    #include <netinet/in.h>
    #include <stdlib.h>
    #include <arpa/inet.h>
    #include <unistd.h>
    #include <sys/select.h>
    #include <sys/queue.h>

typedef struct p_packet_s {
    uint16_t size;
    uint8_t id;
} p_packet_t;

typedef struct p_payload_s {
    struct p_packet_s packet;
    void *data;
} p_payload_t;

typedef struct p_network_data_s {
    int sockfd;
    struct sockaddr_in server_addr;
} p_network_data_t;

typedef struct p_client_s {
    int sockfd;
    p_network_data_t network_data;
    TAILQ_ENTRY(p_client_s) entries;
} p_client_t;

typedef struct p_server_s {
    p_network_data_t network_data;
    fd_set set;
    TAILQ_HEAD(, p_client_s) clients;
} p_server_t;


p_client_t *p_client_create(const char *ip, int port);
p_payload_t* p_client_listen(p_client_t *client);
int p_client_send_packet(
    uint8_t packet_type,
    const void *payload_data,
    size_t payload_size,
    p_client_t *client
);

p_server_t *p_server_create(int port);
p_payload_t* p_server_listen(p_server_t *server);
int p_server_send_packet(
    uint8_t packet_type,
    const void *payload_data,
    size_t payload_size,
    p_server_t *server
);

//typedef struct p_u_login_s {
//    struct p_packet_s packet;
//    char username[MAX_NAME_LENGTH];
//};
//
//typedef struct p_u_logout_s {
//    struct p_packet_s packet;
//};

#endif /* !PROTOCOL_H_ */

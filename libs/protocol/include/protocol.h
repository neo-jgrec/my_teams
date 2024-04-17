/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** protocol
*/

#ifndef PROTOCOL_H_
    #define PROTOCOL_H_

    #include <netinet/in.h>
    #include <sys/queue.h>
    #include <stdbool.h>

    #define DATA_SIZE 4096

/**
 * @struct p_network_data_s
 * @brief Represents network data including socket file descriptor and server
 * address.
 */
typedef struct p_network_data_s {
    int sockfd;                  /**< Socket file descriptor */
    struct sockaddr_in server_addr; /**< Server address */
} p_network_data_t;

/**
 * @struct p_packet_s
 * @brief Represents a packet with type and data.
 */
typedef struct p_packet_s {
    uint16_t type;           // Type of the packet
    uint8_t data[DATA_SIZE]; // Data
} p_packet_t;

/**
 * @struct p_payload_s
 * @brief Represents a payload containing packet, network data, and actual
 * data.
 */
typedef struct p_payload_s {
    p_packet_t packet;                // Packet
    int fd;                           // File descriptor of the client
    TAILQ_ENTRY(p_payload_s) entries; // Entry for TAILQ list
} p_payload_t;

/**
 * @struct p_client_s
 * @brief Represents a client with socket file descriptor and network data.
 */
typedef struct p_client_s {
    fd_set master_read_fds;             // Master file descriptor set
    fd_set master_write_fds;            // Master file descriptor set
    fd_set readfds;                     // File descriptor set
    fd_set writefds;                    // File descriptor set
    int sockfd;                         // Socket file descriptor
    p_network_data_t network_data;      // Network data
    TAILQ_ENTRY(p_client_s) entries;    // Entry for TAILQ list
} p_client_t;

/**
 * @struct p_server_s
 * @brief Represents a server with network data, file descriptor set,
 * and list of clients.
 */
typedef struct p_server_s {
    p_network_data_t network_data; /**< Network data */
    fd_set master_read_fds;     /**< Master file descriptor set */
    fd_set master_write_fds;    /**< Master file descriptor set */
    fd_set read_fds;            /**< File descriptor set */
    fd_set write_fds;           /**< File descriptor set */
    TAILQ_HEAD(, p_client_s) clients; /**< List of clients */
    TAILQ_HEAD(, p_payload_s) payloads; /**< List of payloads */
} p_server_t;

/**
 * @brief Create a client with given IP and port.
 * @param ip IP address of the server.
 * @param port Port number of the server.
 * @return Pointer to the created client.
 */
p_client_t *p_client_create(const char *ip, int port);

/**
 * @brief Listen for incoming packets on the client.
 * @param client Pointer to the client.
 * @param packet Pointer to the packet to be filled.
 * @return True if a packet was received, false otherwise.
 */
bool p_client_listen(p_client_t *client, p_packet_t *packet);

/**
 * @brief Send a packet from the client.
 * @param client Pointer to the client.
 * @param type Type of the packet.
 * @param data Data to be included in the packet.
 * @param size Size of the data.
 * @return True on success, false on failure.
 */
bool p_client_send_packet(const p_client_t *client, uint16_t type,
    const void *data, int size);

/**
 * @brief Create a server with given port.
 * @param port Port number to bind the server.
 * @return Pointer to the created server.
 */
p_server_t *p_server_create(int port);

/**
 * @brief Listen for incoming packets on the server.
 * @param server Pointer to the server.
 * @return Pointer to the received payload.
 */
p_payload_t *p_server_listen(p_server_t *server);

/**
 * @brief Send a packet from the server to a specific client.
 * @param packet Pointer to the packet to be sent.
 * @param client_fd File descriptor of the client.
 * @param server Pointer to the server.
 * @return true on success, false on failure.
 */
bool p_server_send_packet(
    const p_packet_t *packet,
    int client_fd,
    p_server_t *server
);

/**
 * @brief Send a packet from the server to a specific client.
 * @param type Type of the packet.
 * @param client_fd File descriptor of the client.
 * @param server Pointer to the server.
 * @return true on success, false on failure.
 */
bool p_server_send_packet_type(uint16_t type, int client_fd,
    p_server_t *server);

/**
 * @brief Create a payload with given packet type, data, and size.
 * @param packet_type Type of the packet.
 * @param payload_data Data to be included in the payload.
 * @return Pointer to the created payload.
 */
p_payload_t *p_create_payload(
    uint16_t packet_type,
    const void *payload_data
);

/**
 * @brief Create a new client on the server.
 * @param server Pointer to the server.
 * @return true on success, false on failure.
 */
bool new_client(p_server_t *server);

/**
 * @brief Select the server for incoming packets.
 * @param server Pointer to the server.
 * @return true on success, false on failure.
 */
bool select_server(p_server_t *server);

/**
 * @brief Bind the server to the given port.
 * @param server Pointer to the server.
 * @return true on success, false on failure.
 */
bool server_bind(p_server_t *server);

/**
 * @brief Listen for incoming connections on the server.
 * @param server Pointer to the server.
 * @return true on success, false on failure.
 */
bool server_listen(p_server_t *server);

/**
 * @brief Set socket options for the server.
 * @param server Pointer to the server.
 * @return true on success, false on failure.
 */
bool server_setsockopt(p_server_t *server);

/**
 * @brief Create a socket for the server.
 * @param port Port number to bind the server.
 */
p_server_t *server_socket(int port);

/**
 * @brief Get the client with the given file descriptor.
 * @param fd File descriptor of the client.
 * @param server Pointer to the server.
 * @return Pointer to the client.
 */
p_client_t *get_client(int fd, const p_server_t *server);

/**
 * @brief Close the server.
 * @param server Pointer to the server.
 */
void p_server_close(p_server_t *server);

/**
 * @brief Check if the server is open.
 * @return true if the server is open, false otherwise.
 */
bool p_server_is_open(void);

/**
 * @brief Close the client.
 * @param client Pointer to the client.
 */
void p_client_close(p_client_t *client);

#endif /* !PROTOCOL_H_ */

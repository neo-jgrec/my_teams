/*
** EPITECH PROJECT, 2024
** my_teams [WSL: Arch]
** File description:
** client
*/

#ifndef CLIENT_H_
    #define CLIENT_H_

    #include "protocol.h"
    #include "events_structures.h"

    #include <sys/queue.h>
    #include <sys/types.h>

typedef struct queue_node {
    p_packet_t *packet;
    TAILQ_ENTRY(queue_node) entries;
} queue_node_t;

TAILQ_HEAD(queue_head, queue_node);
typedef struct queue_head queue_head_t;

typedef struct {
    p_client_t *p_client;
    queue_head_t queue;
    user_t user;
} c_client_t;

/**
 * @brief main function for the client
 * is only used by main (is returned by the main function)
 *
 * @param ac
 * @param av
 * @return int
 */
int client(int ac, char **av);

/**
 * @brief logs the client
 *
 * @param payload
 */
void client_logger(const p_packet_t *payload, c_client_t *client);

/**
 * @brief Set the payload to zero client object
 *
 * @param payload
 */
void packet_to_zero(p_packet_t *payload);

/**
 * @brief process the priority queue
 *
 */
void process_priority_queue(queue_head_t *queue, c_client_t *client);

/**
 * @brief add a payload to the priority queue
 *
 * @param payload
 */
void add_to_priority_queue(p_packet_t *payload, queue_head_t *queue);

#endif /* !CLIENT_H_ */

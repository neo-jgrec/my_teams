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
    #include <uuid/uuid.h>

typedef struct queue_node {
    p_packet_t *packet;
    TAILQ_ENTRY(queue_node) entries;
} queue_node_t;

TAILQ_HEAD(queue_head, queue_node);
typedef struct queue_head queue_head_t;

typedef struct {
    char team_uuid[UUID_LENGTH];
    char channel_uuid[UUID_LENGTH];
    char thread_uuid[UUID_LENGTH];
} context_t;

typedef struct {
    p_client_t *p_client;
    user_t user;
    context_t context;
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
 * @brief process client input as arguments
 *
 * @return char**
 */
char **get_args_from_input(const char *input);

#endif /* !CLIENT_H_ */

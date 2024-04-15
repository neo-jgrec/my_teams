/*
** EPITECH PROJECT, 2024
** my_teams [WSL: Arch]
** File description:
** client
*/

#ifndef CLIENT_H_
    #define CLIENT_H_

    #include "protocol.h"

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
void client_logger(const p_payload_t *payload);

#endif /* !CLIENT_H_ */

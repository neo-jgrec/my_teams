/*
** EPITECH PROJECT, 2024
** teams [WSL: Arch]
** File description:
** logger
*/

#include "debug_print.h"
#include "logger.h"

void client_logger(const p_packet_t *payload, c_client_t *client)
{
    for (int i = 0; mt_logger[i].func; i++) {
        if (mt_logger[i].type == payload->type) {
            mt_logger[i].func(payload, client);
            return;
        }
    }
}

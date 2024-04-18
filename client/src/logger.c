/*
** EPITECH PROJECT, 2024
** teams [WSL: Arch]
** File description:
** logger
*/

#include "logger.h"
#include <stdio.h>

void client_logger(const p_packet_t *payload, c_client_t *client)
{
    for (int i = 0; mt_logger[i].func; i++) {
        if (mt_logger[i].type == payload->type) {
            mt_logger[i].func(payload, client);
            return;
        }
    }
    printf("%s\n", payload->data);
}

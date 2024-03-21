/*
** EPITECH PROJECT, 2024
** protocol
** File description:
** select_server
*/

#include "../../../include/protocol.h"

int select_server(p_server_t *server)
{
    if (select(FD_SETSIZE, &server->set, NULL, NULL, NULL) == -1) {
        perror("Select failed");
        return -1;
    }
    return 0;
}

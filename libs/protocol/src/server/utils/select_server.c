/*
** EPITECH PROJECT, 2024
** protocol
** File description:
** select_server
*/

#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include "protocol.h"

bool select_server(p_server_t *server)
{
    memcpy(&server->read_fds, &server->master_read_fds, sizeof(fd_set));
    memcpy(&server->write_fds, &server->master_write_fds, sizeof(fd_set));
    return select(
        FD_SETSIZE,
        &server->read_fds,
        &server->write_fds,
        NULL, NULL
    ) != -1;
}

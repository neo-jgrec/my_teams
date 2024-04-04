/*
** EPITECH PROJECT, 2024
** protocol
** File description:
** select_server
*/

#include "../../../include/protocol.h"
#include "../../../../../include/debug_print.h"

int select_server(p_server_t *server)
{
    if (select(
        FD_SETSIZE,
        &server->read_fds,
        &server->write_fds,
        NULL, NULL
    ) == -1) {
        DEBUG_PRINT("Select failed: %s\n", strerror(errno));
        return -1;
    }
    return 0;
}

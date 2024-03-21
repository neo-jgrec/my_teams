/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** p_server_create
*/

#include "../include/protocol.h"
#include "../include/protocol_server.h"

static void p_server_stop(int sig)
{
    if (sig != SIGINT)
        return;
    exit(0);
}

p_server_t *p_server_create(int port)
{
    p_server_t *server = server_socket(port);
    struct sigaction sig = {0};

    if (!server)
        return NULL;
    if (server_setsockopt(server) == -1)
        return NULL;
    if (server_bind(server) == -1)
        return NULL;
    TAILQ_INIT(&server->clients);
    if (server_listen(server) == -1)
        return NULL;
    signal(SIGPIPE, SIG_IGN);
    sig.sa_handler = p_server_stop;
    sigaction(SIGINT, &sig, NULL);
    return server;
}

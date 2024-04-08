/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** p_server_create
*/

#include "protocol.h"

static void p_server_stop(const int sig)
{
    if (sig != SIGINT)
        return;
    exit(0);
}

p_server_t *p_server_create(const int port)
{
    p_server_t *server = server_socket(port);
    struct sigaction sig = {0};

    if (!server || !server_setsockopt(server) || !server_bind(server))
        return NULL;
    TAILQ_INIT(&server->clients);
    if (!server_listen(server))
        return NULL;
    signal(SIGPIPE, SIG_IGN);
    sig.sa_handler = p_server_stop;
    sigaction(SIGINT, &sig, NULL);
    return server;
}

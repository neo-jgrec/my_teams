/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** p_server_create
*/

#include "protocol.h"

static bool p_server_open_state(const bool new_state, const bool set)
{
    static bool state = false;

    if (set)
        state = new_state;
    return state;
}

static void p_server_stop(const int sig)
{
    if (sig == SIGINT)
        p_server_open_state(false, true);
}

bool p_server_is_open(void)
{
    return p_server_open_state(false, false);
}

p_server_t *p_server_create(const int port)
{
    p_server_t *server = server_socket(port);
    struct sigaction sig = {0};

    if (!server || !server_setsockopt(server) || !server_bind(server))
        return NULL;
    TAILQ_INIT(&server->clients);
    TAILQ_INIT(&server->payloads);
    if (!server_listen(server))
        return NULL;
    signal(SIGPIPE, SIG_IGN);
    sig.sa_handler = p_server_stop;
    sigaction(SIGINT, &sig, NULL);
    p_server_open_state(true, true);
    return server;
}

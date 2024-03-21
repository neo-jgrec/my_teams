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

static p_server_t *server_socket(int port)
{
    p_server_t *server = (p_server_t*)malloc(sizeof(p_server_t));

    server->network_data.sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (server->network_data.sockfd < 0) {
        perror("Socket creation failed");
        free(server);
        return NULL;
    }
    server->network_data.server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server->network_data.server_addr.sin_family = AF_INET;
    server->network_data.server_addr.sin_port = htons(port);
    return server;
}

static int server_setsockopt(p_server_t *server)
{
    if (setsockopt(
        server->network_data.sockfd, SOL_SOCKET, SO_REUSEADDR,
        &server->network_data.server_addr.sin_addr, sizeof(int)
    ) == -1) {
        perror("Setsockopt failed");
        close(server->network_data.sockfd);
        free(server);
        return -1;
    }
    return 0;
}

static int server_bind(p_server_t *server)
{
    if (bind(
        server->network_data.sockfd,
        (const struct sockaddr *)&server->network_data.server_addr,
        sizeof(server->network_data.server_addr)
    ) == -1) {
        perror("Bind failed");
        close(server->network_data.sockfd);
        free(server);
        return -1;
    }
    return 0;
}

static int server_listen(p_server_t *server)
{
    if (listen(server->network_data.sockfd, SOMAXCONN) == -1) {
        perror("Listen failed");
        close(server->network_data.sockfd);
        free(server);
        return -1;
    }
    return 0;
}

p_server_t* p_server_create(int port)
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
/*
** EPITECH PROJECT, 2024
** teams [WSL: Arch]
** File description:
** login
*/

#include "commands.h"
#include "events.h"
#include "protocol.h"
#include "unused.h"

p_payload_t *cmd_login(char **args, UNUSED void *data)
{
    size_t nb_args = 0;

    for (; args[nb_args]; nb_args++);
    if (nb_args != 2)
        return p_create_payload(INT16_MAX - 1, "Invalid number of arguments\n");
    fprintf(stdout, "Logging in with username: %s\n", args[1]);
    p_client_send_packet(EVT_LOGIN, args[1], (p_client_t *)data);
    return p_create_payload(INT16_MAX, "Login sent to server\n");
}

/*
** EPITECH PROJECT, 2024
** my_teams [WSL: Arch]
** File description:
** main
*/

#include <stdlib.h>

#include "server.h"

int main(const int ac, char **av)
{
    if (ac != 2)
        return EXIT_FAILURE;
    server(av[1]);
    return EXIT_SUCCESS;
}

/*
** EPITECH PROJECT, 2024
** my_teams [WSL: Arch]
** File description:
** help
*/

#include "commands.h"
#include "unused.h"
#include "asprintf.h"
#include <stdlib.h>
#include <string.h>


static response_t standard_help(char **buffer)
{
    response_t mem_error = {
        .status = 500,
        .message = "Memory allocation error",
        .data = NULL,
    };

    for (int i = 0; commands[i].name; i++) {
        if (asprintf(buffer, "%s%s\n",
            *buffer ? *buffer : "", commands[i].description) == -1) {
            return mem_error;
        }
    }
    return (response_t){
        .status = 200,
        .message = "Help command executed successfully",
        .data = *buffer,
    };
}

response_t cmd_help(char **args, UNUSED void *data)
{
    char *buffer = NULL;

    if (!args[0]) {
        return (response_t){
            .status = 404,
            .message = "Help command failed (invalid arguments)",
            .is_success = 0,
            .data = NULL,
        };
    }
    return standard_help(&buffer);
}

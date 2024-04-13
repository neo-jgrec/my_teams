/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** uuid
*/

#include <uuid/uuid.h>
#include <stdlib.h>

#include "../../include/server.h"

char *get_uuid(void)
{
    uuid_t id;
    char *uuid = malloc(UUID_LENGTH);

    if (!uuid)
        return NULL;
    uuid_generate(id);
    uuid[UUID_LENGTH - 1] = '\0';
    return uuid;
}
/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** uuid
*/

#include <uuid/uuid.h>
#include <stdlib.h>

#include "server.h"

char *get_uuid(void)
{
    uuid_t id;
    char *uuid = malloc(UUID_LENGTH);

    if (!uuid)
        return NULL;
    uuid_generate(id);
    uuid_unparse(id, uuid);
    uuid[UUID_LENGTH - 1] = '\0';
    return uuid;
}

char *get_uuid_no_malloc(char *uuid)
{
    uuid_t id;

    uuid_generate(id);
    uuid_unparse(id, uuid);
    uuid[UUID_LENGTH - 1] = '\0';
    return uuid;
}

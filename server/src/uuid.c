/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** uuid
*/

#include <stdlib.h>
#include <uuid/uuid.h>

char *get_uuid(void)
{
    uuid_t id;
    char *uuid = malloc(37);

    if (!uuid)
        return NULL;
    uuid_generate(id);
    uuid[36] = '\0';
    return uuid;
}

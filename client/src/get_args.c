/*
** EPITECH PROJECT, 2024
** teams [WSL: Arch]
** File description:
** get_args
*/

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

static char *fill_line(const char *str, int *pos, char separator)
{
    bool in_quotes = false;
    const char *start = str + *pos;
    const char *end = start;
    char *result;

    for (; (*end != separator || in_quotes) && *end != '\0'; end++) {
        if (*end == '"' || *end == '\'')
            in_quotes = !in_quotes;
    }
    *pos += end - start;
    result = strndup(start, end - start);
    result[strlen(result) - 1] = (result[strlen(result) - 1] == '\n'
        ? '\0' : result[strlen(result) - 1]);
    return result;
}

char **get_args_from_input(const char *input)
{
    int space_count = 0;
    char **args = NULL;
    int i = 0;
    int pos = 0;

    for (const char *ptr = input; *ptr; ptr++)
        space_count += (*ptr == ' ');
    args = malloc(sizeof(char *) * (space_count + 2));
    if (!args)
        return NULL;
    while (input[pos]) {
        args[i] = fill_line(input, &pos, ' ');
        if (!args[i])
            return NULL;
        i++;
        for (; input[pos] && input[pos] == ' '; pos++);
    }
    args[i] = NULL;
    return args;
}

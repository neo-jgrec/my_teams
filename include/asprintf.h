/*
** EPITECH PROJECT, 2024
** my_teams [WSL: Arch]
** File description:
** asprintf
*/

#ifndef ASPRINTF_H_
    #define ASPRINTF_H_

    #ifndef asprintf
        #ifndef _GNU_SOURCE
            #define _GNU_SOURCE
        #endif
        #include <stdio.h>

int asprintf(char **strp, const char *fmt, ...);
    #endif

#endif /* !ASPRINTF_H_ */

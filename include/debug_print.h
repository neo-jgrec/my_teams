/*
** EPITECH PROJECT, 2024
** my_teams [WSL: Arch]
** File description:
** debug_print
*/

#ifndef DEBUG_PRINT_H_
#define DEBUG_PRINT_H_

#ifndef _GNU_SOURCE
    #define _GNU_SOURCE
#endif

#ifdef DEBUG
    #ifndef fprintf
        #include <stdio.h>
    #endif

    #define _D_GREEN_ANSII "\033[0;32m"
    #define _D_END_ANSII "\033[0m"

    #define _D_STRING _D_GREEN_ANSII "[DEBUG] " _D_END_ANSII "%s:%d:%s():"

    #define DEBUG_PRINT(fmt, ...) fprintf(stderr, _D_STRING fmt, \
        __FILE__, __LINE__, __func__, ##__VA_ARGS__)
#else
    #define DEBUG_PRINT(fmt, ...)
#endif

#endif /* !DEBUG_PRINT_H_ */

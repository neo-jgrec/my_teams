/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** protocol
*/

#ifndef PROTOCOL_H_
    #define PROTOCOL_H_

    #include <stdio.h>
    #include <stdint.h>

    #define MAX_NAME_LENGTH 32
    #define MAX_DESCRIPTION_LENGTH 255
    #define MAX_BODY_LENGTH 512

typedef struct p_packet_s {
    uint16_t size;
    uint8_t id;
};

typedef struct p_u_login_s {
    struct p_packet_s packet;
    char username[MAX_NAME_LENGTH];
};

typedef struct p_u_logout_s {
    struct p_packet_s packet;
};

#endif /* !PROTOCOL_H_ */

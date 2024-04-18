/*
** EPITECH PROJECT, 2024
** my_teams [WSL: Arch]
** File description:
** commands
*/

#ifndef COMMANDS_H_
    #define COMMANDS_H_

    #include "protocol.h"
    #include <stdbool.h>
    #include <stddef.h>

    #define MAX_NAME_LENGTH 32
    #define MAX_DESCRIPTION_LENGTH 255
    #define MAX_BODY_LENGTH 512

typedef struct command_s {
    char *name;
    char *description;
    void (*func)(char **args, void *data, p_packet_t *packet);
    bool need_login;
} command_t;

void cmd_help(char **args, void *data, p_packet_t *packet);
void cmd_login(char **args, void *data, p_packet_t *packet);
void cmd_logout(char **args, void *data, p_packet_t *packet);
void cmd_users(char **args, void *data, p_packet_t *packet);
void cmd_user(char **args, void *data, p_packet_t *packet);
void cmd_send(char **args, void *data, p_packet_t *packet);
void cmd_messages(char **args, void *data, p_packet_t *packet);
void cmd_subscribe(char **args, void *data, p_packet_t *packet);
void cmd_subscribed(char **args, void *data, p_packet_t *packet);
void cmd_unsubscribe(char **args, void *data, p_packet_t *packet);
void cmd_use(char **args, void *data, p_packet_t *packet);
void cmd_create(char **args, void *data, p_packet_t *packet);
void cmd_list(char **args, void *data, p_packet_t *packet);
void cmd_info(char **args, void *data, p_packet_t *packet);

static const command_t commands[] = {
    {
        "/help",
        "/help : show help",
        cmd_help,
        false
    },
    {
        "/login",
        "/login [“user_name”] : set the user_name used by client",
        cmd_login,
        false
    },
    {
        "/logout",
        "/logout : disconnect the client from the server",
        cmd_logout,
        true
    },
    {
        "/users",
        "/users : get the list of all users that exist on the domain",
        cmd_users,
        true
    },
    {
        "/user",
        "/user [“user_uuid”] : get details about the requested user",
        NULL,
        true
    },
    {
        "/send",
        "/send [“user_uuid”] [“message_body”] :"
        " send a message to specific user",
        NULL,
        true
    },
    {
        "/messages",
        "/messages [“user_uuid”] : list all messages"
        " exchanged with the specified user",
        NULL,
        true
    },
    {
        "/subscribe",
        "/subscribe [“team_uuid”] : subscribe to the events of a team and "
        "its sub directories (enable reception of all events from a team)",
        NULL,
        true
    },
    {
        "/subscribed",
        "/subscribed ?[“team_uuid”] : list all subscribed teams"
        " or list all users subscribed to a team",
        cmd_subscribed,
        true
    },
    {
        "/unsubscribe",
        "/unsubscribe [“team_uuid”] : unsubscribe from a team",
        NULL,
        true
    },
    {
        "/use",
        "/use ?[“team_uuid”] ?[“channel_uuid”] ?[“thread_uuid”] : "
        "Sets the command context to a team/channel/thread",
        cmd_use,
        true
    },
    {
        "/create",
        "/create : based on the context, create the"
        " sub resource (see /help create)",
        NULL,
        true
    },
    {
        "/list",
        "/list : based on the context, list all the sub"
        "resources (see /help list)",
        NULL,
        true
    },
    {
        "/info",
        "/info : based on the context, display details of"
        " the current resource (see /help info)",
        NULL,
        true
    },
    {
        NULL,
        NULL,
        NULL,
        false
    }
};

#endif /* !COMMANDS_H_ */

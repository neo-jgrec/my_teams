/*
** EPITECH PROJECT, 2024
** teams [WSL: Arch]
** File description:
** subscibed
*/

#include "client.h"
#include "commands.h"
#include "events.h"
#include "protocol.h"
#include "unused.h"

#include <stdio.h>
#include <string.h>

static void no_args(c_client_t *client, UNUSED char **args)
{
    p_client_t *p_client = client->p_client;

    p_client_send_packet(
        p_client,
        EVT_LIST_SUBSCRIBED_TEAMS,
        NULL,
        0
    );
}

static void subscribed_teams(c_client_t *client, char **args)
{
    p_client_t *p_client = client->p_client;
    team_uuid_t team_uuid = {0};

    memcpy(team_uuid.uuid, args[1], sizeof(team_uuid.uuid));
    p_client_send_packet(
        p_client,
        EVT_LIST_SUBSCRIBED_IN_TEAM,
        &team_uuid,
        sizeof(team_uuid)
    );
}

void cmd_subscribed(char **args, void *data, UNUSED p_packet_t *packet)
{
    size_t nb_args = 0;
    static const struct {
        uint8_t nb_args;
        void (*func)(c_client_t *client, char **args);
    } __args_uses[] = {
        {1, no_args},
        {2, subscribed_teams},
        {0, NULL}
    };

    for (; args[nb_args]; nb_args++);
    for (int i = 0; __args_uses[i].func; i++) {
        if (__args_uses[i].nb_args == nb_args) {
            __args_uses[i].func((c_client_t *)data, args);
            return;
        }
    }
    fprintf(stdout, "Invalid command\n");
}

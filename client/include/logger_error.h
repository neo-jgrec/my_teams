/*
** EPITECH PROJECT, 2024
** teams [WSL: Arch]
** File description:
** logger_error
*/

#ifndef LOGGER_ERROR_H_
    #define LOGGER_ERROR_H_

    #include "protocol.h"
    #include "client.h"
    #include "logging_client.h"
    #include "events_structures.h"
    #include "unused.h"

    #include <string.h>

static inline void mt_error_unknown_team(const p_packet_t *payload,
    UNUSED c_client_t *client)
{
    team_uuid_t team_uuid = {0};

    memcpy(&team_uuid, payload->data, sizeof(team_uuid_t));
    client_error_unknown_team(team_uuid.uuid);
}

static inline void mt_error_unknown_channel(const p_packet_t *payload,
    UNUSED c_client_t *client)
{
    team_uuid_t team_uuid = {0};

    memcpy(&team_uuid, payload->data, sizeof(team_uuid_t));
    client_error_unknown_channel(team_uuid.uuid);
}

static inline void mt_error_unknown_thread(const p_packet_t *payload,
    UNUSED c_client_t *client)
{
    team_uuid_t team_uuid = {0};

    memcpy(&team_uuid, payload->data, sizeof(team_uuid_t));
    client_error_unknown_thread(team_uuid.uuid);
}

static inline void mt_error_unknown_user(const p_packet_t *payload,
    UNUSED c_client_t *client)
{
    team_uuid_t user_uuid = {0};

    memcpy(&user_uuid, payload->data, sizeof(team_uuid_t));
    client_error_unknown_user(user_uuid.uuid);
}

static inline void mt_error_unauthorized(UNUSED const p_packet_t *payload,
    UNUSED c_client_t *client)
{
    client_error_unauthorized();
}

static inline void mt_already_exist(UNUSED const p_packet_t *payload,
    UNUSED c_client_t *client)
{
    client_error_already_exist();
}

#endif /* !LOGGER_ERROR_H_ */

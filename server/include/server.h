/*
** EPITECH PROJECT, 2024
** my_teams [WSL: Arch]
** File description:
** server
*/

#ifndef SERVER_H_
    #define SERVER_H_

    #include "protocol.h"

typedef struct {} s_server_t;

/**
 * @brief Create a server
 * @param str_port The port to listen on
 */
void server(const char *str_port);

/**
 * @brief Get a UUID (version 4)
 * @return The UUID
 */
char *get_uuid(void);

typedef char name_t[32];
typedef char description_t[255];
typedef char body_t[37];

typedef char uuid_t[37];
typedef uint8_t data_t[DATA_SIZE];

typedef struct {
    name_t user_name;
} login_t;

/**
 * @brief Handle login event
 * @param server The server
 * @param payload The payload
 */
void s_server_event_logged_in(s_server_t *server, const p_payload_t *payload);

typedef struct {
    uuid_t user_uuid;
} logout_t;

/**
 * @brief Handle disconnect event
 * @param server The server
 * @param payload The payload
 */
void s_server_event_logged_out(s_server_t *server, const p_payload_t *payload);

/**
 * @brief Handle list users event
 * @param server The server
 * @param payload The payload
 */
void s_server_event_list_users(s_server_t *server, const p_payload_t *payload);

typedef struct {
    uuid_t user_uuid;
    body_t message_body;
} send_message_t;

/**
 * @brief Handle send message event
 * @param server The server
 * @param payload The payload
 */
void s_server_event_send_message(s_server_t *server,
    const p_payload_t *payload);

typedef struct {
    uuid_t user_uuid;
} list_messages_t;

/**
 * @brief Handle list messages event
 * @param server The server
 * @param payload The payload
 */
void s_server_event_list_messages(s_server_t *server,
    const p_payload_t *payload);

typedef struct {
    uuid_t user_uuid;
    uuid_t team_uuid;
} subscribe_t;

/**
 * @brief Handle subscribe event
 * @param server The server
 * @param payload The payload
 */
void s_server_event_subscribe(s_server_t *server, const p_payload_t *payload);

typedef struct {
    uuid_t team_uuid;
} list_subscribed_users_in_team_t;

/**
 * @brief Handle list subscribed users in team event
 * @param server The server
 * @param payload The payload
 */
void s_server_event_list_subscribed_users_in_team(s_server_t *server,
    const p_payload_t *payload);

typedef struct {
    uuid_t user_uuid;
} list_subscribed_teams_t;

/**
 * @brief Handle list subscribed teams event
 * @param server The server
 * @param payload The payload
 */
void s_server_event_list_subscribed_teams(s_server_t *server,
    const p_payload_t *payload);

typedef struct {
    uuid_t user_uuid;
    uuid_t team_uuid;
} unsubscribe_t;

/**
 * @brief Handle unsubscribe event
 * @param server The server
 * @param payload The payload
 */
void s_server_event_unsubscribe(s_server_t *server, const p_payload_t *payload);

typedef struct {
    uuid_t user_uuid;
    name_t team_name;
} team_create_t;

/**
 * @brief Handle create team event
 * @param server The server
 * @param payload The payload
 */
void s_server_event_team_created(s_server_t *server,
    const p_payload_t *payload);

typedef struct {
    uuid_t team_uuid;
    name_t channel_name;
} channel_create_t;

/**
 * @brief Handle create channel event
 * @param server The server
 * @param payload The payload
 */
void s_server_event_channel_created(s_server_t *server,
    const p_payload_t *payload);

typedef struct {
    uuid_t channel_uuid;
    uuid_t user_uuid;
    name_t thread_title;
    body_t thread_body;
} thread_create_t;

/**
 * @brief Handle create thread event
 * @param server The server
 * @param payload The payload
 */
void s_server_event_thread_created(s_server_t *server,
    const p_payload_t *payload);

typedef struct {
    uuid_t channel_uuid;
    uuid_t user_uuid;
    body_t reply_body;
} reply_create_t;

/**
 * @brief Handle create reply event
 * @param server The server
 * @param payload The payload
 */
void s_server_event_reply_created(s_server_t *server,
    const p_payload_t *payload);

typedef struct {
    uuid_t user_uuid;
} list_teams_t;

/**
 * @brief Handle list teams event
 * @param server The server
 * @param payload The payload
 */
void s_server_event_list_teams(s_server_t *server, const p_payload_t *payload);

typedef struct {
    uuid_t team_uuid;
} list_channels_t;

/**
 * @brief Handle list channels event
 * @param server The server
 * @param payload The payload
 */
void s_server_event_list_channels(s_server_t *server,
    const p_payload_t *payload);

typedef struct {
    uuid_t channel_uuid;
} list_threads_t;

/**
 * @brief Handle list threads event
 * @param server The server
 * @param payload The payload
 */
void s_server_event_list_threads(s_server_t *server,
    const p_payload_t *payload);

typedef struct {
    uuid_t thread_uuid;
} list_replies_t;

/**
 * @brief Handle list replies event
 * @param server The server
 * @param payload The payload
 */
void s_server_event_list_replies(s_server_t *server,
    const p_payload_t *payload);

typedef struct {
    uuid_t user_uuid;
} user_info_t;

/**
 * @brief Handle get user info event
 * @param server The server
 * @param payload The payload
 */
void s_server_event_get_user_info(s_server_t *server,
    const p_payload_t *payload);

typedef struct {
    uuid_t team_uuid;
} team_info_t;

/**
 * @brief Handle get team info event
 * @param server The server
 * @param payload The payload
 */
void s_server_event_get_team_info(s_server_t *server,
    const p_payload_t *payload);

typedef struct {
    uuid_t channel_uuid;
} channel_info_t;

/**
 * @brief Handle get channel info event
 * @param server The server
 * @param payload The payload
 */
void s_server_event_get_channel_info(s_server_t *server,
    const p_payload_t *payload);

typedef struct {
    uuid_t thread_uuid;
} thread_info_t;

/**
 * @brief Handle get thread info event
 * @param server The server
 * @param payload The payload
 */
void s_server_event_get_thread_info(s_server_t *server,
    const p_payload_t *payload);

/**
 * @brief Handle ping event
 * @param server The server
 * @param payload The payload
 */
void s_server_event_ping(s_server_t *server, const p_payload_t *payload);

#endif /* !SERVER_H_ */

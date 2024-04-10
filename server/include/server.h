/*
** EPITECH PROJECT, 2024
** my_teams [WSL: Arch]
** File description:
** server
*/

#ifndef SERVER_H_
    #define SERVER_H_

    #include "protocol.h"

typedef struct {
    char uuid[37];
    char name[32];
} user_t;

typedef struct {
    user_t user;
    TAILQ_ENTRY(s_user_s) entries;
} s_user_t;

typedef struct {
    char uuid[37];
    char name[32];
    char description[255];
} team_t;

typedef struct {
    team_t team;
    TAILQ_ENTRY(s_team_s) entries;
} s_team_t;

typedef struct {
    char uuid[37];
    char name[32];
    char description[255];
} channel_t;

typedef struct {
    channel_t channel;
    TAILQ_ENTRY(s_channel_s) entries;
} s_channel_t;

typedef struct {
    char uuid[37];
    char title[32];
    char body[37];
} thread_t;

typedef struct {
    thread_t thread;
    TAILQ_ENTRY(s_thread_s) entries;
} s_thread_t;

typedef struct {
    s_user_t users;
    s_team_t teams;
    s_channel_t channels;
    s_thread_t threads;

    p_server_t *socket;
} s_server_t;

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

typedef struct {
    char user_name[32];
} login_t;

/**
 * @brief Handle login event
 * @param server The server
 * @param payload The payload
 */
void s_server_event_logged_in(s_server_t *server, const p_payload_t *payload);

typedef struct {
    char user_uuid[37];
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
    char user_uuid[37];
    char message_body[37];
} send_message_t;

/**
 * @brief Handle send message event
 * @param server The server
 * @param payload The payload
 */
void s_server_event_send_message(s_server_t *server,
    const p_payload_t *payload);

typedef struct {
    char user_uuid[37];
} list_messages_t;

/**
 * @brief Handle list messages event
 * @param server The server
 * @param payload The payload
 */
void s_server_event_list_messages(s_server_t *server,
    const p_payload_t *payload);

typedef struct {
    char user_uuid[37];
    char team_uuid[37];
} subscribe_t;

/**
 * @brief Handle subscribe event
 * @param server The server
 * @param payload The payload
 */
void s_server_event_subscribe(s_server_t *server, const p_payload_t *payload);

typedef struct {
    char team_uuid[37];
} list_subscribed_users_in_team_t;

/**
 * @brief Handle list subscribed users in team event
 * @param server The server
 * @param payload The payload
 */
void s_server_event_list_subscribed_users_in_team(s_server_t *server,
    const p_payload_t *payload);

typedef struct {
    char user_uuid[37];
} list_subscribed_teams_t;

/**
 * @brief Handle list subscribed teams event
 * @param server The server
 * @param payload The payload
 */
void s_server_event_list_subscribed_teams(s_server_t *server,
    const p_payload_t *payload);

typedef struct {
    char user_uuid[37];
    char team_uuid[37];
} unsubscribe_t;

/**
 * @brief Handle unsubscribe event
 * @param server The server
 * @param payload The payload
 */
void s_server_event_unsubscribe(s_server_t *server,
    const p_payload_t *payload);

typedef struct {
    char user_uuid[37];
    char team_name[32];
} team_create_t;

/**
 * @brief Handle create team event
 * @param server The server
 * @param payload The payload
 */
void s_server_event_team_created(s_server_t *server,
    const p_payload_t *payload);

typedef struct {
    char team_uuid[37];
    char channel_name[32];
} channel_create_t;

/**
 * @brief Handle create channel event
 * @param server The server
 * @param payload The payload
 */
void s_server_event_channel_created(s_server_t *server,
    const p_payload_t *payload);

typedef struct {
    char channel_uuid[37];
    char user_uuid[37];
    char thread_title[32];
    char thread_body[37];
} thread_create_t;

/**
 * @brief Handle create thread event
 * @param server The server
 * @param payload The payload
 */
void s_server_event_thread_created(s_server_t *server,
    const p_payload_t *payload);

typedef struct {
    char channel_uuid[37];
    char user_uuid[37];
    char reply_body[37];
} reply_create_t;

/**
 * @brief Handle create reply event
 * @param server The server
 * @param payload The payload
 */
void s_server_event_reply_created(s_server_t *server,
    const p_payload_t *payload);

typedef struct {
    char user_uuid[37];
} list_teams_t;

/**
 * @brief Handle list teams event
 * @param server The server
 * @param payload The payload
 */
void s_server_event_list_teams(s_server_t *server, const p_payload_t *payload);

typedef struct {
    char team_uuid[37];
} list_channels_t;

/**
 * @brief Handle list channels event
 * @param server The server
 * @param payload The payload
 */
void s_server_event_list_channels(s_server_t *server,
    const p_payload_t *payload);

typedef struct {
    char channel_uuid[37];
} list_threads_t;

/**
 * @brief Handle list threads event
 * @param server The server
 * @param payload The payload
 */
void s_server_event_list_threads(s_server_t *server,
    const p_payload_t *payload);

typedef struct {
    char thread_uuid[37];
} list_replies_t;

/**
 * @brief Handle list replies event
 * @param server The server
 * @param payload The payload
 */
void s_server_event_list_replies(s_server_t *server,
    const p_payload_t *payload);

typedef struct {
    char user_uuid[37];
} user_info_t;

/**
 * @brief Handle get user info event
 * @param server The server
 * @param payload The payload
 */
void s_server_event_get_user_info(s_server_t *server,
    const p_payload_t *payload);

typedef struct {
    char team_uuid[37];
} team_info_t;

/**
 * @brief Handle get team info event
 * @param server The server
 * @param payload The payload
 */
void s_server_event_get_team_info(s_server_t *server,
    const p_payload_t *payload);

typedef struct {
    char channel_uuid[37];
} channel_info_t;

/**
 * @brief Handle get channel info event
 * @param server The server
 * @param payload The payload
 */
void s_server_event_get_channel_info(s_server_t *server,
    const p_payload_t *payload);

typedef struct {
    char thread_uuid[37];
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

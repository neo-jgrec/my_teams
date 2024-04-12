/*
** EPITECH PROJECT, 2024
** my_teams [WSL: Arch]
** File description:
** server
*/

#ifndef SERVER_H_
    #define SERVER_H_

    #include "protocol.h"

    #define UUID_LENGTH 37
    #define MAX_NAME_LENGTH 32
    #define MAX_DESCRIPTION_LENGTH 255
    #define MAX_BODY_LENGTH 512

typedef struct {
    char uuid[UUID_LENGTH];
    char name[MAX_NAME_LENGTH];
} user_t;

typedef struct s_user_s {
    user_t user;
    TAILQ_ENTRY(s_user_s) entries;
} s_user_t;

typedef struct {
    char uuid[UUID_LENGTH];
    char name[MAX_NAME_LENGTH];
    char description[MAX_DESCRIPTION_LENGTH];
} team_t;

typedef struct s_team_s {
    team_t team;
    TAILQ_ENTRY(s_team_s) entries;
} s_team_t;

typedef struct {
    char uuid[UUID_LENGTH];
    char team_uuid[UUID_LENGTH];
    char name[MAX_NAME_LENGTH];
    char description[MAX_DESCRIPTION_LENGTH];
} channel_t;

typedef struct s_channel_s {
    channel_t channel;
    TAILQ_ENTRY(s_channel_s) entries;
} s_channel_t;

typedef struct {
    char uuid[UUID_LENGTH];
    char channel_uuid[UUID_LENGTH];
    char title[MAX_NAME_LENGTH];
    char body[MAX_BODY_LENGTH];
} thread_t;

typedef struct s_thread_s {
    thread_t thread;
    TAILQ_ENTRY(s_thread_s) entries;
} s_thread_t;

typedef struct {
    char user_uuid[UUID_LENGTH];
    char thread_uuid[UUID_LENGTH];
    char body[MAX_BODY_LENGTH];
} reply_t;

typedef struct s_reply_s {
    reply_t reply;
    TAILQ_ENTRY(s_reply_s) entries;
} s_reply_t;

typedef struct {
    char sender_uuid[UUID_LENGTH];
    char receiver_uuid[UUID_LENGTH];
    char body[MAX_BODY_LENGTH];
} private_message_t;

typedef struct s_private_message_s {
    private_message_t message;
    TAILQ_ENTRY(s_private_message_s) entries;
} s_private_message_t;

typedef struct {
    char user_uuid[UUID_LENGTH];
    char team_uuid[UUID_LENGTH];
} subscribe_t;

typedef struct s_subscribe_s {
    subscribe_t subscribe;
    TAILQ_ENTRY(s_subscribe_s) entries;
} s_subscribe_t;

typedef struct {
    TAILQ_HEAD(, s_user_s) users;

    TAILQ_HEAD(, s_team_s) teams;

    TAILQ_HEAD(, s_channel_s) channels;

    TAILQ_HEAD(, s_thread_s) threads;

    TAILQ_HEAD(, s_reply_s) replies;

    TAILQ_HEAD(, s_private_message_s) private_messages;

    TAILQ_HEAD(, s_subscribe_s) subscribes;

    TAILQ_HEAD(, s_user_s) logged;

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
    char user_name[MAX_NAME_LENGTH];
} login_t;

/**
 * @brief Handle login event
 * @param server The server
 * @param payload The payload
 */
void s_server_event_logged_in(s_server_t *server, const p_payload_t *payload);

typedef struct {
    char user_uuid[UUID_LENGTH];
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
    char sender_uuid[UUID_LENGTH];
    char receiver_uuid[UUID_LENGTH];
    char message_body[MAX_BODY_LENGTH];
} send_message_t;

/**
 * @brief Handle send message event
 * @param server The server
 * @param payload The payload
 */
void s_server_event_send_message(s_server_t *server,
    const p_payload_t *payload);

typedef struct {
    char user_uuid[UUID_LENGTH];
} list_messages_t;

/**
 * @brief Handle list messages event
 * @param server The server
 * @param payload The payload
 */
void s_server_event_list_messages(s_server_t *server,
    const p_payload_t *payload);

/**
 * @brief Handle subscribe event
 * @param server The server
 * @param payload The payload
 */
void s_server_event_subscribe(s_server_t *server, const p_payload_t *payload);

typedef struct {
    char team_uuid[UUID_LENGTH];
} list_subscribed_users_in_team_t;

/**
 * @brief Handle list subscribed users in team event
 * @param server The server
 * @param payload The payload
 */
void s_server_event_list_subscribed_users_in_team(s_server_t *server,
    const p_payload_t *payload);

typedef struct {
    char user_uuid[UUID_LENGTH];
} list_subscribed_teams_t;

/**
 * @brief Handle list subscribed teams event
 * @param server The server
 * @param payload The payload
 */
void s_server_event_list_subscribed_teams(s_server_t *server,
    const p_payload_t *payload);

typedef struct {
    char user_uuid[UUID_LENGTH];
    char team_uuid[UUID_LENGTH];
} unsubscribe_t;

/**
 * @brief Handle unsubscribe event
 * @param server The server
 * @param payload The payload
 */
void s_server_event_unsubscribe(s_server_t *server,
    const p_payload_t *payload);

typedef struct {
    char user_uuid[UUID_LENGTH];
    char team_name[MAX_NAME_LENGTH];
} team_create_t;

/**
 * @brief Handle create team event
 * @param server The server
 * @param payload The payload
 */
void s_server_event_team_created(s_server_t *server,
    const p_payload_t *payload);

typedef struct {
    char team_uuid[UUID_LENGTH];
    char channel_name[MAX_NAME_LENGTH];
} channel_create_t;

/**
 * @brief Handle create channel event
 * @param server The server
 * @param payload The payload
 */
void s_server_event_channel_created(s_server_t *server,
    const p_payload_t *payload);

typedef struct {
    char channel_uuid[UUID_LENGTH];
    char user_uuid[UUID_LENGTH];
    char thread_title[MAX_NAME_LENGTH];
    char thread_body[MAX_BODY_LENGTH];
} thread_create_t;

/**
 * @brief Handle create thread event
 * @param server The server
 * @param payload The payload
 */
void s_server_event_thread_created(s_server_t *server,
    const p_payload_t *payload);

typedef struct {
    char thread_uui[UUID_LENGTH];
    char user_uuid[UUID_LENGTH];
    char reply_body[MAX_BODY_LENGTH];
} reply_create_t;

/**
 * @brief Handle create reply event
 * @param server The server
 * @param payload The payload
 */
void s_server_event_reply_created(s_server_t *server,
    const p_payload_t *payload);

typedef struct {
    char user_uuid[UUID_LENGTH];
} list_teams_t;

/**
 * @brief Handle list teams event
 * @param server The server
 * @param payload The payload
 */
void s_server_event_list_teams(s_server_t *server, const p_payload_t *payload);

typedef struct {
    char team_uuid[UUID_LENGTH];
} list_channels_t;

/**
 * @brief Handle list channels event
 * @param server The server
 * @param payload The payload
 */
void s_server_event_list_channels(s_server_t *server,
    const p_payload_t *payload);

typedef struct {
    char channel_uuid[UUID_LENGTH];
} list_threads_t;

/**
 * @brief Handle list threads event
 * @param server The server
 * @param payload The payload
 */
void s_server_event_list_threads(s_server_t *server,
    const p_payload_t *payload);

typedef struct {
    char thread_uuid[UUID_LENGTH];
} list_replies_t;

/**
 * @brief Handle list replies event
 * @param server The server
 * @param payload The payload
 */
void s_server_event_list_replies(s_server_t *server,
    const p_payload_t *payload);

typedef struct {
    char user_uuid[UUID_LENGTH];
} user_info_t;

/**
 * @brief Handle get user info event
 * @param server The server
 * @param payload The payload
 */
void s_server_event_get_user_info(s_server_t *server,
    const p_payload_t *payload);

typedef struct {
    char team_uuid[UUID_LENGTH];
} team_info_t;

/**
 * @brief Handle get team info event
 * @param server The server
 * @param payload The payload
 */
void s_server_event_get_team_info(s_server_t *server,
    const p_payload_t *payload);

typedef struct {
    char channel_uuid[UUID_LENGTH];
} channel_info_t;

/**
 * @brief Handle get channel info event
 * @param server The server
 * @param payload The payload
 */
void s_server_event_get_channel_info(s_server_t *server,
    const p_payload_t *payload);

typedef struct {
    char thread_uuid[UUID_LENGTH];
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

/**
 * @brief Send a success response
 * @param server The server
 * @param payload The payload
 */
void send_success(const s_server_t *server, const p_payload_t *payload);

/**
 * @brief Send an error response
 * @param server The server
 * @param payload The payload
 */
void send_error(const s_server_t *server, const p_payload_t *payload);

/**
 * @brief Send a UUID response
 * @param server The server
 * @param payload The payload
 * @param uuid The UUID
 */
void send_uuid(const s_server_t *server, const p_payload_t *payload,
    const char *uuid);

/**
 * @brief Send a UUID process response
 * @param server The server
 * @param payload The payload
 * @param uuid The UUID
 */
void send_uuid_process(const s_server_t *server, const p_payload_t *payload,
    const char *uuid);

#endif /* !SERVER_H_ */

/*
** EPITECH PROJECT, 2024
** my_teams [WSL: Arch]
** File description:
** server
*/

#ifndef SERVER_H_
    #define SERVER_H_

    #include "events_structures.h"
    #include "protocol.h"

    #define SEND_TYPE (void)p_server_send_packet_type
    #define COMBINE(x, y) (x << 8) + y
    #define ERROR_PACKET(x, y) COMBINE(x, y), payload->fd, server->socket

    #define SAVE_FILE ".save.out"

typedef struct s_user_s {
    user_t user;
    TAILQ_ENTRY(s_user_s) entries;
} s_user_t;

typedef struct s_team_s {
    team_t team;
    TAILQ_ENTRY(s_team_s) entries;
} s_team_t;

typedef struct s_channel_s {
    channel_t channel;
    TAILQ_ENTRY(s_channel_s) entries;
} s_channel_t;

typedef struct s_thread_s {
    thread_t thread;
    TAILQ_ENTRY(s_thread_s) entries;
} s_thread_t;

typedef struct s_reply_s {
    reply_t reply;
    TAILQ_ENTRY(s_reply_s) entries;
} s_reply_t;

typedef struct s_private_message_s {
    private_message_t message;
    TAILQ_ENTRY(s_private_message_s) entries;
} s_private_message_t;

typedef struct s_subscribe_s {
    subscribe_t subscribe;
    TAILQ_ENTRY(s_subscribe_s) entries;
} s_subscribe_t;

typedef struct {
    char uuid[UUID_LENGTH];
    char name[MAX_NAME_LENGTH];
    int socket;
} logged_user_t;

typedef struct s_logged_user_s {
    logged_user_t user;
    TAILQ_ENTRY(s_logged_user_s) entries;
} s_logged_user_t;

typedef struct {
    TAILQ_HEAD(, s_user_s) users;
    TAILQ_HEAD(, s_team_s) teams;
    TAILQ_HEAD(, s_channel_s) channels;
    TAILQ_HEAD(, s_thread_s) threads;
    TAILQ_HEAD(, s_reply_s) replies;
    TAILQ_HEAD(, s_private_message_s) private_messages;
    TAILQ_HEAD(, s_subscribe_s) subscribes;
    TAILQ_HEAD(, s_logged_user_s) logged;

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

/**
 * @brief Get a UUID (version 4) without malloc
 * @param uuid The UUID
 * @return The UUID
 */
char *get_uuid_no_malloc(char *uuid);

/**
 * @brief Save the server
 * @param server The server
 * @return true if the server was saved, false otherwise
 */
bool save(s_server_t *server);

/**
 * @brief Load the server
 * @param server The server
 */
void load(s_server_t *server);

/**
 * @brief Clear the server
 * @param server The server
 */
void clear_server(s_server_t *server);

/**
 * @brief Handle login event
 * @param server The server
 * @param payload The payload
 */
void s_server_event_logged_in(s_server_t *server, const p_payload_t *payload);

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

/**
 * @brief Handle send message event
 * @param server The server
 * @param payload The payload
 */
void s_server_event_send_message(s_server_t *server,
    const p_payload_t *payload);

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

/**
 * @brief Handle list subscribed users in team event
 * @param server The server
 * @param payload The payload
 */
void s_server_event_list_subscribed_users_in_team(s_server_t *server,
    const p_payload_t *payload);

/**
 * @brief Handle list subscribed teams event
 * @param server The server
 * @param payload The payload
 */
void s_server_event_list_subscribed_teams(s_server_t *server,
    const p_payload_t *payload);

/**
 * @brief Handle unsubscribe event
 * @param server The server
 * @param payload The payload
 */
void s_server_event_unsubscribe(s_server_t *server,
    const p_payload_t *payload);

/**
 * @brief Handle create team event
 * @param server The server
 * @param payload The payload
 */
void s_server_event_team_created(s_server_t *server,
    const p_payload_t *payload);

/**
 * @brief Handle create channel event
 * @param server The server
 * @param payload The payload
 */
void s_server_event_channel_created(s_server_t *server,
    const p_payload_t *payload);

/**
 * @brief Handle create thread event
 * @param server The server
 * @param payload The payload
 */
void s_server_event_thread_created(s_server_t *server,
    const p_payload_t *payload);

/**
 * @brief Handle create reply event
 * @param server The server
 * @param payload The payload
 */
void s_server_event_reply_created(s_server_t *server,
    const p_payload_t *payload);

/**
 * @brief Handle list teams event
 * @param server The server
 * @param payload The payload
 */
void s_server_event_list_teams(s_server_t *server, const p_payload_t *payload);

/**
 * @brief Handle list channels event
 * @param server The server
 * @param payload The payload
 */
void s_server_event_list_channels(s_server_t *server,
    const p_payload_t *payload);

/**
 * @brief Handle list threads event
 * @param server The server
 * @param payload The payload
 */
void s_server_event_list_threads(s_server_t *server,
    const p_payload_t *payload);

/**
 * @brief Handle list replies event
 * @param server The server
 * @param payload The payload
 */
void s_server_event_list_replies(s_server_t *server,
    const p_payload_t *payload);

/**
 * @brief Handle get user info event
 * @param server The server
 * @param payload The payload
 */
void s_server_event_get_user_info(s_server_t *server,
    const p_payload_t *payload);

/**
 * @brief Handle get team info event
 * @param server The server
 * @param payload The payload
 */
void s_server_event_get_team_info(s_server_t *server,
    const p_payload_t *payload);

/**
 * @brief Handle get channel info event
 * @param server The server
 * @param payload The payload
 */
void s_server_event_get_channel_info(s_server_t *server,
    const p_payload_t *payload);

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
 * @brief Check if a user is in a team
 * @param server The server
 * @param user_uuid The user UUID
 * @param team_uuid The team UUID
 * @return true if the user is in the team, false otherwise
 */
bool is_in_teams(const s_server_t *server, const char *user_uuid,
    const char *team_uuid);

/**
 * @brief Check if a user is in a channel
 * @param server The server
 * @param user_uuid The user UUID
 * @param channel_uuid The channel UUID
 * @return true if the user is in the channel, false otherwise
 */
bool is_in_channels(const s_server_t *server, const char *user_uuid,
    const char *channel_uuid);

/**
 * @brief Check if a user is in a thread
 * @param server The server
 * @param user_uuid The user UUID
 * @param thread_uuid The thread UUID
 * @return true if the user is in the thread, false otherwise
 */
bool is_in_threads(const s_server_t *server, const char *user_uuid,
    const char *thread_uuid);

/**
 * @brief Check if a user is logged
 * @param server The server
 * @param user_uuid The user UUID
 * @return true if the user is logged, false otherwise
 */
bool is_logged(const s_server_t *server, const char *user_uuid);

/**
 * @brief Check if a team exists
 * @param server The server
 * @param fd The client file descriptor
 * @param team_uuid The team UUID
 * @param type The packet type
 */
bool check_team_exist(s_server_t *server, int fd, const char *team_uuid,
    uint16_t type);

/**
 * @brief Check if a channel exists
 * @param server The server
 * @param fd The client file descriptor
 * @param channel_uuid The channel UUID
 * @param type The packet type
 */
bool check_channel_exist(s_server_t *server, int fd, const char *channel_uuid,
    uint16_t type);

/**
 * @brief Check if a thread exists
 * @param server The server
 * @param fd The client file descriptor
 * @param thread_uuid The thread UUID
 * @param type The packet type
 */
bool check_thread_exist(s_server_t *server, int fd, const char *thread_uuid,
    uint16_t type);

/**
 * @brief Check if a user exists
 * @param server The server
 * @param fd The client file descriptor
 * @param user_uuid The user UUID
 * @param type The packet type
 */
bool check_user_exist(s_server_t *server, int fd, const char *user_uuid,
    uint16_t type);

/**
 * @brief Check if a UUID is allocated
 * @param server The server
 * @param fd The client file descriptor
 * @param uuid The UUID
 * @param type The packet type
 */
bool check_uuid(s_server_t *server, int fd, char **uuid, uint16_t type);

#endif /* !SERVER_H_ */

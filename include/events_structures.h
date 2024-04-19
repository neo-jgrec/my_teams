/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** events_structures
*/

#ifndef EVENTS_STRUCTURES_H
    #define EVENTS_STRUCTURES_H

    #define UUID_LENGTH 37
    #define MAX_NAME_LENGTH 32
    #define MAX_DESCRIPTION_LENGTH 255
    #define MAX_BODY_LENGTH 512

    #include <stdbool.h>
    #include <time.h>

// No Struct request for EVT_PING and EVT_LIST_USERS
// No Struct response for EVT_PING and EVT_SEND

/**
 * @details Struct response for EVT_LOGIN and EVT_DISCONNECT
 */
typedef struct {
    char uuid[UUID_LENGTH];
    char name[MAX_NAME_LENGTH];
} user_t;

/**
 * @details Struct request for EVT_LIST_USERS, EVT_INFO_USER
 * and EVT_LIST_SUBSCRIBED_IN_TEAM
 */
typedef struct {
    char uuid[UUID_LENGTH];
    char name[MAX_NAME_LENGTH];
    bool is_logged;
} user_state_t;

/**
 * @details Struct response for EVT_CREATE_TEAM, EVT_INFO_TEAM,
 * EVT_LIST_TEAMS and EVT_TEAM_CREATE, EVT_LIST_SUBSCRIBED_TEAMS
 */
typedef struct {
    char uuid[UUID_LENGTH];
    char name[MAX_NAME_LENGTH];
    char description[MAX_DESCRIPTION_LENGTH];
} team_t;

/**
 * @details Struct response for EVT_LIST_MESSAGES
 */
typedef struct {
    char sender_uuid[UUID_LENGTH];
    char receiver_uuid[UUID_LENGTH];
    char body[MAX_BODY_LENGTH];
    time_t timestamp;
} private_message_t;

/**
 * @details Struct request for EVT_SUBSCRIBE
 * @details Struct response for EVT_SUBSCRIBE
 * and EVT_UNSUBSCRIBE
 */
typedef struct {
    char user_uuid[UUID_LENGTH];
    char team_uuid[UUID_LENGTH];
} subscribe_t;

/**
 * @details Struct request for EVT_LOGIN
 */
typedef struct {
    char user_name[MAX_NAME_LENGTH];
} login_t;

/**
 * @details Struct request for EVT_DISCONNECT, EVT_LIST_MESSAGES,
 * EVT_LIST_SUBSCRIBED_IN_TEAM, EVT_LIST_SUBSCRIBED_TEAMS, EVT_LIST_TEAMS,
 * EVT_LIST_CHANNELS, EVT_LIST_THREADS, EVT_LIST_REPLIES, EVT_INFO_USER,
 * EVT_INFO_CHANNEL, EVT_INFO_THREAD and EVT_INFO_REPLY
 */
typedef struct {
    char uuid[UUID_LENGTH];
} team_uuid_t;

/**
 * @details Struct request for EVT_SEND
 * @details Struct response for EVT_MESSAGE_RECEIVE
 */
typedef struct {
    char sender_uuid[UUID_LENGTH];
    char receiver_uuid[UUID_LENGTH];
    char message_body[MAX_BODY_LENGTH];
} send_message_t;

/**
 * @details Struct request for EVT_UNSUBSCRIBE
 */
typedef struct {
    char user_uuid[UUID_LENGTH];
    char team_uuid[UUID_LENGTH];
} unsubscribe_t;

/**
 * @details Struct request for EVT_CREATE_TEAM
 */
typedef struct {
    char user_uuid[UUID_LENGTH];
    char team_name[MAX_NAME_LENGTH];
    char team_description[MAX_DESCRIPTION_LENGTH];
} team_create_t;

/**
 * @details Struct request for EVT_CREATE_CHANNEL
 */
typedef struct {
    char user_uuid[UUID_LENGTH];
    char team_uuid[UUID_LENGTH];
    char channel_name[MAX_NAME_LENGTH];
    char channel_description[MAX_DESCRIPTION_LENGTH];
} channel_create_t;

/**
 * @details Struct response for EVT_CREATE_CHANNEL, EVT_CHANNEL_CREATE,
 * EVT_INFO_CHANNEL and EVT_LIST_CHANNELS
 */
typedef struct {
    char uuid[UUID_LENGTH];
    char team_uuid[UUID_LENGTH];
    char name[MAX_NAME_LENGTH];
    char description[MAX_DESCRIPTION_LENGTH];
} channel_t;

/**
 * @details Struct request for EVT_CREATE_THREAD
 */
typedef struct {
    char channel_uuid[UUID_LENGTH];
    char user_uuid[UUID_LENGTH];
    char thread_title[MAX_NAME_LENGTH];
    char thread_body[MAX_BODY_LENGTH];
} thread_create_t;

/**
 * @details Struct response for EVT_THREAD_CREATE, EVT_CREATE_THREAD,
 * EVT_LIST_THREADS and EVT_INFO_THREAD
 */
typedef struct {
    char uuid[UUID_LENGTH];
    char user_uuid[UUID_LENGTH];
    char channel_uuid[UUID_LENGTH];
    char title[MAX_NAME_LENGTH];
    char body[MAX_BODY_LENGTH];
    time_t timestamp;
} thread_t;

/**
 * @details Struct request for EVT_CREATE_REPLY
 */
typedef struct {
    char thread_uuid[UUID_LENGTH];
    char user_uuid[UUID_LENGTH];
    char reply_body[MAX_BODY_LENGTH];
} reply_create_t;

/**
 * @details Struct response for EVT_LIST_REPLIES and EVT_CREATE_REPLY
 */
typedef struct {
    char user_uuid[UUID_LENGTH];
    char thread_uuid[UUID_LENGTH];
    char body[MAX_BODY_LENGTH];
    time_t timestamp;
} reply_t;

/**
 * @details Struct request for EVT_REPLY_CREATE
 */
typedef struct {
    char team_uuid[UUID_LENGTH];
    char user_uuid[UUID_LENGTH];
    char thread_uuid[UUID_LENGTH];
    char reply_body[MAX_BODY_LENGTH];
} reply_ref_t;

#endif //EVENTS_STRUCTURES_H

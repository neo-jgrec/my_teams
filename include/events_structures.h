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

/**
 *  No Structure for EVT_INFO_TEAM and EVT_PING
 */

/**
 * @brief Struct for EVT_LIST_USERS
 */
typedef struct {
    char uuid[UUID_LENGTH];
    char name[MAX_NAME_LENGTH];
} user_t;

/**
 * @brief Struct for EVT_SUBSCRIBE

 */
typedef struct {
    char user_uuid[UUID_LENGTH];
    char team_uuid[UUID_LENGTH];
} subscribe_t;

/**
 * @brief Struct for EVT_LOGIN
 */
typedef struct {
    char user_name[MAX_NAME_LENGTH];
} login_t;

/**
 * @brief Struct for EVT_DISCONNECT
 */
typedef struct {
    char user_uuid[UUID_LENGTH];
} logout_t;

/**
 * @brief Struct for EVT_SEND_MESSAGE, EVT_MESSAGE_RECEIVE
 */
typedef struct {
    char sender_uuid[UUID_LENGTH];
    char receiver_uuid[UUID_LENGTH];
    char message_body[MAX_BODY_LENGTH];
} send_message_t;

/**
 * @brief Struct for EVT_LIST_MESSAGES
 */
typedef struct {
    char user_uuid[UUID_LENGTH];
} list_messages_t;

/**
 * @brief Struct for EVT_LIST_SUBSCRIBED_IN_TEAM
 */
typedef struct {
    char team_uuid[UUID_LENGTH];
} list_subscribed_users_in_team_t;

/**
 * @brief Struct for EVT_LIST_SUBSCRIBED_TEAMS
 */
typedef struct {
    char user_uuid[UUID_LENGTH];
} list_subscribed_teams_t;

/**
 * @brief Struct for EVT_UNSUBSCRIBE
 */
typedef struct {
    char user_uuid[UUID_LENGTH];
    char team_uuid[UUID_LENGTH];
} unsubscribe_t;

/**
 * @brief Struct for EVT_CREATE_TEAM, EVT_TEAM_CREATE
 */
typedef struct {
    char user_uuid[UUID_LENGTH];
    char team_name[MAX_NAME_LENGTH];
} team_create_t;

/**
 * @brief Struct for EVT_CREATE_CHANNEL, EVT_CHANNEL_CREATE
 */
typedef struct {
    char team_uuid[UUID_LENGTH];
    char channel_name[MAX_NAME_LENGTH];
} channel_create_t;

/**
 * @brief Struct for EVT_CREATE_THREAD, EVT_THREAD_CREATE
 */
typedef struct {
    char channel_uuid[UUID_LENGTH];
    char user_uuid[UUID_LENGTH];
    char thread_title[MAX_NAME_LENGTH];
    char thread_body[MAX_BODY_LENGTH];
} thread_create_t;

/**
 * @brief Struct for EVT_CREATE_REPLY, EVT_REPLY_CREATE
 */
typedef struct {
    char thread_uui[UUID_LENGTH];
    char user_uuid[UUID_LENGTH];
    char reply_body[MAX_BODY_LENGTH];
} reply_create_t;

/**
 * @brief Struct for EVT_LIST_TEAMS
 */
typedef struct {
    char user_uuid[UUID_LENGTH];
} list_teams_t;

/**
 * @brief Struct for EVT_LIST_CHANNELS
 */
typedef struct {
    char team_uuid[UUID_LENGTH];
} list_channels_t;

/**
 * @brief Struct for EVT_LIST_THREADS
 */
typedef struct {
    char channel_uuid[UUID_LENGTH];
} list_threads_t;

/**
 * @brief Struct for EVT_LIST_REPLIES
 */
typedef struct {
    char thread_uuid[UUID_LENGTH];
} list_replies_t;

/**
 * @brief Struct for EVT_INFO_USER
 */
typedef struct {
    char user_uuid[UUID_LENGTH];
} user_info_t;

/**
 * @brief Struct for EVT_INFO_CHANNEL
 */
typedef struct {
    char team_uuid[UUID_LENGTH];
} team_info_t;

/**
 * @brief Struct for EVT_INFO_THREAD
 */
typedef struct {
    char channel_uuid[UUID_LENGTH];
} channel_info_t;

/**
 * @brief Struct for EVT_INFO_REPLY
 */
typedef struct {
    char thread_uuid[UUID_LENGTH];
} thread_info_t;

#endif //EVENTS_STRUCTURES_H

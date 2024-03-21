/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** protocol_client
*/

#ifndef PROTOCOL_CLIENT_H_
    #define PROTOCOL_CLIENT_H_

/**
 * @enum client_event_e
 * @brief Represents various events that can occur on the client side.
 */
typedef enum client_event_e {
    EVT_LOGIN, /**< Event: Login */
    EVT_DISCONNECT, /**< Event: Disconnect */
    EVT_USERS, /**< Event: List Users */
    EVT_USER, /**< Event: Get User */
    EVT_SEND, /**< Event: Send Message */
    EVT_MESSAGES, /**< Event: List Messages */
    EVT_SUBSCRIBE, /**< Event: Subscribe to a User */
    EVT_SUBSCRIBED_IN_TEAM, /**< Event: List Subscribed Users in Team */
    EVT_SUBSCRIBED_TEAMS, /**< Event: List Subscribed Teams */
    EVT_UNSUBSCRIBE, /**< Event: Unsubscribe from a User */
    EVT_CREATE_TEAM, /**< Event: Create Team */
    EVT_CREATE_CHANNEL, /**< Event: Create Channel */
    EVT_CREATE_THREAD, /**< Event: Create Thread */
    EVT_CREATE_REPLY, /**< Event: Create Reply */
    EVT_LIST_TEAMS, /**< Event: List Teams */
    EVT_LIST_CHANNELS, /**< Event: List Channels */
    EVT_LIST_THREADS, /**< Event: List Threads */
    EVT_LIST_REPLIES, /**< Event: List Replies */
    EVT_INFO_USER, /**< Event: Get User Info */
    EVT_INFO_TEAM, /**< Event: Get Team Info */
    EVT_INFO_CHANNEL, /**< Event: Get Channel Info */
    EVT_INFO_THREAD, /**< Event: Get Thread Info */
    EVT_PING /**< Event: Ping */
} client_event_t;

#endif /* !PROTOCOL_CLIENT_H_ */

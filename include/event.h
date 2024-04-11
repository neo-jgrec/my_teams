/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** event
*/

#ifndef EVENT_H
    #define EVENT_H

typedef enum {
    EVT_LOGIN, /**< Event: Login */
    EVT_DISCONNECT, /**< Event: Disconnect */
    EVT_LIST_USERS, /**< Event: List Users */
    EVT_SEND, /**< Event: Send Message */
    EVT_LIST_MESSAGES, /**< Event: List Messages */
    EVT_SUBSCRIBE, /**< Event: Subscribe to a User */
    EVT_LIST_SUBSCRIBED_IN_TEAM, /**< Event: List Subscribed Users in Team */
    EVT_LIST_SUBSCRIBED_TEAMS, /**< Event: List Subscribed Teams */
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
    EVT_PING, /**< Event: Ping */
    NB_EVT /**< Number of Events */
} client_event_t;

typedef enum {
    EVT_CONTINUE, /**< Event: Continue */
    EVT_SUCCESS, /**< Event: Success */
    EVT_ERROR, /**< Event: Error */
} server_event_t;

#endif //EVENT_H

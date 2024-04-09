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
    EVTC_LOGIN, /**< Event: Login */
    EVTC_DISCONNECT, /**< Event: Disconnect */
    EVTC_USERS, /**< Event: List Users */
    EVTC_USER, /**< Event: Get User */
    EVTC_SEND, /**< Event: Send Message */
    EVTC_MESSAGES, /**< Event: List Messages */
    EVTC_SUBSCRIBE, /**< Event: Subscribe to a User */
    EVTC_SUBSCRIBED_IN_TEAM, /**< Event: List Subscribed Users in Team */
    EVTC_SUBSCRIBED_TEAMS, /**< Event: List Subscribed Teams */
    EVTC_UNSUBSCRIBE, /**< Event: Unsubscribe from a User */
    EVTC_CREATE_TEAM, /**< Event: Create Team */
    EVTC_CREATE_CHANNEL, /**< Event: Create Channel */
    EVTC_CREATE_THREAD, /**< Event: Create Thread */
    EVTC_CREATE_REPLY, /**< Event: Create Reply */
    EVTC_LIST_TEAMS, /**< Event: List Teams */
    EVTC_LIST_CHANNELS, /**< Event: List Channels */
    EVTC_LIST_THREADS, /**< Event: List Threads */
    EVTC_LIST_REPLIES, /**< Event: List Replies */
    EVTC_INFO_USER, /**< Event: Get User Info */
    EVTC_INFO_TEAM, /**< Event: Get Team Info */
    EVTC_INFO_CHANNEL, /**< Event: Get Channel Info */
    EVTC_INFO_THREAD, /**< Event: Get Thread Info */
    EVTC_PING /**< Event: Ping */
} client_event_t;

#endif /* !PROTOCOL_CLIENT_H_ */

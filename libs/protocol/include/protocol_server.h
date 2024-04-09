/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** protocol_server
*/

#ifndef PROTOCOL_SERVER_H_
    #define PROTOCOL_SERVER_H_

/**
 * @enum server_event_e
 * @brief Represents various events that can occur on the server side.
 */
typedef enum server_event_e {
    EVTS_ERROR, /**< Event: Error */
    EVTS_SUCCESS, /**< Event: Success */
    EVTS_INFO_USER, /**< Event: User Info */
    EVTS_INFO_TEAM, /**< Event: Team Info */
    EVTS_INFO_CHANNEL, /**< Event: Channel Info */
    EVTS_INFO_THREAD, /**< Event: Thread Info */
    EVTS_INFO_REPLY, /**< Event: Reply Info */
    EVTS_INFO_MESSAGE, /**< Event: Message Info */
    EVTS_INFO_SUBSCRIPTION, /**< Event: Subscription Info */
    EVTS_INFO_UNSUBSCRIBE /**< Event: Unsubscribe Info */
} server_event_t;

#endif /* !PROTOCOL_SERVER_H_ */

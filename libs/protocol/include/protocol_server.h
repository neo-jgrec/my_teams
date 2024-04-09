/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** protocol_server
*/

#ifndef PROTOCOL_SERVER_H_
    #define PROTOCOL_SERVER_H_

typedef enum server_event_e {
    EVT_ERROR,
    EVT_SUCCESS,
    EVT_INFO_USER,
    EVT_INFO_TEAM,
    EVT_INFO_CHANNEL,
    EVT_INFO_THREAD,
    EVT_INFO_REPLY,
    EVT_INFO_MESSAGE,
    EVT_INFO_SUBSCRIPTION,
    EVT_INFO_UNSUBSCRIBE
} server_event_t;

#endif /* !PROTOCOL_SERVER_H_ */

/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** events
*/

#ifndef EVENTS_H_
    #define EVENTS_H_

/**
 * @enum event_t
 * @brief Type of events that can be send to the server
 */
typedef enum {
    EVT_LOGIN,                          // Event: Login
    EVT_DISCONNECT,                     // Event: Disconnect
    EVT_LIST_USERS,                     // Event: List Users
    EVT_SEND,                           // Event: Send Message
    EVT_LIST_MESSAGES,                  // Event: List Messages
    EVT_SUBSCRIBE,                      // Event: Subscribe to a User
    EVT_LIST_SUBSCRIBED_IN_TEAM,        // Event: List Subscribed Users in Team
    EVT_LIST_SUBSCRIBED_TEAMS,          // Event: List Subscribed Teams
    EVT_UNSUBSCRIBE,                    // Event: Unsubscribe from a User
    EVT_CREATE_TEAM,                    // Event: Create Team
    EVT_CREATE_CHANNEL,                 // Event: Create Channel
    EVT_CREATE_THREAD,                  // Event: Create Thread
    EVT_CREATE_REPLY,                   // Event: Create Reply
    EVT_LIST_TEAMS,                     // Event: List Teams
    EVT_LIST_CHANNELS,                  // Event: List Channels
    EVT_LIST_THREADS,                   // Event: List Threads
    EVT_LIST_REPLIES,                   // Event: List Replies
    EVT_INFO_USER,                      // Event: Get User Info
    EVT_INFO_TEAM,                      // Event: Get Team Info
    EVT_INFO_CHANNEL,                   // Event: Get Channel Info
    EVT_INFO_THREAD,                    // Event: Get Thread Info
    EVT_PING,                           // Event: Ping

    NB_EVT,                             // Number of Events

    EVT_MESSAGE_RECEIVE,                // Event: Message Receive
    EVT_REPLY_CREATE,                   // Event: Reply Create
    EVT_TEAM_CREATE,                    // Event: Team Create
    EVT_THREAD_CREATE,                  // Event: Thread Create
    EVT_CHANNEL_CREATE,                 // Event: Channel Create

    EVT_CONTINUE,                       // Event: Continue

    EVT_ERROR,                          // Event: Error
    EVT_ERROR_UNKNOWN,                  // Event: Error Unknown
    EVT_ERROR_UNAUTHORIZED,             // Event: Error Unauthorized
    EVT_ERROR_ALREADY,                  // Event: Error Already Subscribed
} event_t;

#endif /* !EVENTS_H_ */

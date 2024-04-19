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
    // client_event_logged_in
    EVT_LOGIN,                      // Event: Login
    // client_event_logged_out
    EVT_DISCONNECT,                 // Event: Disconnect
    // client_print_users
    EVT_LIST_USERS,                 // Event: List Users
    EVT_SEND,                       // Event: Send Message
    // client_private_message_print_messages
    EVT_LIST_MESSAGES,              // Event: List Messages
    // client_print_subscribed
    EVT_SUBSCRIBE,                  // Event: Subscribe to a User
    EVT_LIST_SUBSCRIBED_IN_TEAM,    // Event: List Subscribed Users in Team
    EVT_LIST_SUBSCRIBED_TEAMS,      // Event: List Subscribed Teams
    // client_print_unsubscribed
    EVT_UNSUBSCRIBE,                // Event: Unsubscribe from a User
    // client_print_team_created
    EVT_CREATE_TEAM,                // Event: Create Team
    // client_print_channel_created
    EVT_CREATE_CHANNEL,             // Event: Create Channel
    // client_print_thread_created
    EVT_CREATE_THREAD,              // Event: Create Thread
    // client_print_reply_created
    EVT_CREATE_REPLY,               // Event: Create Reply
    // client_print_teams
    EVT_LIST_TEAMS,                 // Event: List Teams
    // client_team_print_channels
    EVT_LIST_CHANNELS,              // Event: List Channels
    // client_channel_print_threads
    EVT_LIST_THREADS,               // Event: List Threads
    // client_thread_print_replies
    EVT_LIST_REPLIES,               // Event: List Replies
    // client_print_user
    EVT_INFO_USER,                  // Event: Get User Info
    // client_print_team
    EVT_INFO_TEAM,                  // Event: Get Team Info
    // client_print_channel
    EVT_INFO_CHANNEL,               // Event: Get Channel Info
    // client_print_thread
    EVT_INFO_THREAD,                // Event: Get Thread Info
    EVT_PING,                       // Event: Ping

    NB_EVT,                         // Number of Events

    // client_event_private_message_received
    EVT_MESSAGE_RECEIVE,             // Event: Message Receive
    // client_event_thread_reply_received
    EVT_REPLY_CREATE,                // Event: Reply Create
    // client_event_team_created
    EVT_TEAM_CREATE,                 // Event: Team Create
    // client_event_channel_created
    EVT_CHANNEL_CREATE,              // Event: Channel Create
    // client_event_thread_created
    EVT_THREAD_CREATE,               // Event: Thread Create

    EVT_CONTINUE,                    // Event: Continue

    EVT_ERROR,                       // Event: Error
    EVT_ERROR_UNKNOWN,               // Event: Error Unknown
    EVT_ERROR_UNKNOWN_TEAM,          // Event: Error Unknown Team
    EVT_ERROR_UNKNOWN_CHANNEL,       // Event: Error Unknown Channel
    EVT_ERROR_UNKNOWN_THREAD,        // Event: Error Unknown Thread
    EVT_ERROR_UNKNOWN_USER,          // Event: Error Unknown User
    EVT_ERROR_UNAUTHORIZED,          // Event: Error Unauthorized
    EVT_ERROR_ALREADY,               // Event: Error Already Subscribed

    EVT_SERVER_CLOSE,                // Event: Server Close
} event_t;

#endif /* !EVENTS_H_ */

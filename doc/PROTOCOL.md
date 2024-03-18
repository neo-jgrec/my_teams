# RFC Protocol

## Header Structure

The header of each packet follows the following structure:

```
|----------------------------|----------------------|-------------------|
| Payload Length (2 bytes)   | Packet Type (1 byte) | Payload (n bytes) |
|----------------------------|----------------------|-------------------|
```

The `Payload Length` field is a 2-byte unsigned integer that represents the length of the `Payload` field. The `Packet Type` field is a 1-byte unsigned integer that represents the type of the packet. The `Payload` field is a variable-length field that contains the actual data of the packet.

## Packet Types

| Type | Name | Require login | Payload | Description |
|------|------|---------------|---------|-------------|
| 0x00 | Login | No | `username` (string) | The client sends this packet to the server to authenticate itself. |
| 0x01 | Disconnect | Yes | `reason` (string) | The client sends this packet to the server to disconnect from the server. |
| 0x02 | Users | Yes | `users` (array of strings) | The server sends this packet to the client to update the list of users. |
| 0x03 | User | Yes | `username` (string) | The server sends this packet to the client to notify it that a new user has connected. |
| 0x04 | Send | Yes | `username` (string), `message` (string) | The client sends this packet to the server to send a message to another user. The server sends this packet to the client to notify it that a new message has been received. |
| 0x05 | Messages | Yes | `messages` (array of objects) | The server sends this packet to the client to update the list of messages. |
| 0x06 | Subscribe | Yes | `username` (string) | The client sends this packet to the server to subscribe to the messages of another user. |
| 0x07 | Subscribed in team | Yes | `username` (string) | The server sends this packet to the client to notify it that a new user has subscribed to its messages. |
| 0x08 | Subscribed teams | Yes | `teams` (array of strings) | The server sends this packet to the client to update the list of teams. |
| 0x09 | Unsubscribe | Yes | `username` (string) | The client sends this packet to the server to unsubscribe from the messages of another user. |
| 0x10 | Create team | Yes | `team` (string) | The client sends this packet to the server to create a new team. |
| 0x11 | Create channel | Yes | `channel` (string) | The client sends this packet to the server to create a new channel. |
| 0x12 | Create thread | Yes | `thread` (string) | The client sends this packet to the server to create a new thread. |
| 0x13 | Create reply | Yes | `reply` (string) | The client sends this packet to the server to create a new reply. |
| 0x14 | List teams | Yes | `teams` (array of strings) | The client sends this packet to the server to list the teams. |
| 0x15 | List channels | Yes | `channels` (array of strings) | The client sends this packet to the server to list the channels. |
| 0x16 | List threads | Yes | `threads` (array of strings) | The client sends this packet to the server to list the threads. |
| 0x17 | List replies | Yes | `replies` (array of strings) | The client sends this packet to the server to list the replies. |
| 0x18 | Info user | Yes | `username` (string) | The client sends this packet to the server to get the information of a user. |
| 0x19 | Info team | Yes | `team` (string) | The client sends this packet to the server to get the information of a team. |
| 0x20 | Info channel | Yes | `channel` (string) | The client sends this packet to the server to get the information of a channel. |
| 0x21 | Info thread | Yes | `thread` (string) | The client sends this packet to the server to get the information of a thread. |
| 0x22 | Ping | Yes | `timestamp` (number) | The client sends this packet to the server to check if it is still connected. |

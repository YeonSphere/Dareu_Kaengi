#include "ipc.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to initialize IPC
void init_ipc() {
    printf("IPC initialized.\n");
}

// Function to send a message
void send_message(int sender_id, int receiver_id, const char *message) {
    Message *msg = (Message *)malloc(sizeof(Message));
    msg->sender_id = sender_id;
    msg->receiver_id = receiver_id;
    strncpy(msg->message, message, sizeof(msg->message));
    // Implement message sending logic here
    printf("Message sent from %d to %d: %s\n", sender_id, receiver_id, message);
    free(msg);
}

// Function to receive a message
void receive_message(int receiver_id, Message *msg) {
    // Implement message receiving logic here
    printf("Message received by %d: %s\n", receiver_id, msg->message);
}

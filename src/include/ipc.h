#ifndef IPC_H
#define IPC_H

// Define the Message structure
typedef struct {
    int sender_id;
    int receiver_id;
    char message[256];
} Message;

// Function prototypes for IPC
void init_ipc();
void send_message(int sender_id, int receiver_id, const char *message);
void receive_message(int receiver_id, Message *msg);

#endif // IPC_H

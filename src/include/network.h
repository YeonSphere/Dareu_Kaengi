#ifndef NETWORK_H
#define NETWORK_H

#include <stddef.h>

// Function prototypes for network support
void init_network();
void send_packet(const char *data);
void receive_packet(char *buffer, size_t size);

#endif // NETWORK_H

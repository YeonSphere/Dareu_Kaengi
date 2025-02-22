#ifndef MEMORY_H
#define MEMORY_H

#include <stddef.h>

// Function prototypes for memory management
void init_memory_management();
void setup_memory_map();
void enable_paging();
void *allocate_memory(size_t size);
void free_memory(void *ptr);

#endif // MEMORY_H

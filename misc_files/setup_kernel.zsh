#!/bin/zsh

# Set the project directory to the current directory
PROJECT_DIR="$(pwd)"

# Clean old files
echo "Cleaning old files..."
rm -rf "${PROJECT_DIR}/build"
rm -rf "${PROJECT_DIR}/src"

# Create necessary directories
echo "Creating directory structure..."
mkdir -p "${PROJECT_DIR}/build"
mkdir -p "${PROJECT_DIR}/src/kernel"
mkdir -p "${PROJECT_DIR}/src/drivers"
mkdir -p "${PROJECT_DIR}/src/modules"
mkdir -p "${PROJECT_DIR}/src/include"
mkdir -p "${PROJECT_DIR}/src/boot"

# Create and populate kernel.c
cat <<EOL > "${PROJECT_DIR}/src/kernel/kernel.c"
#include <stdio.h>
#include <unistd.h>
#include "kernel.h"
#include "memory.h"
#include "scheduler.h"

#define NUM_PROCESSES 5

void entry_point(void) {
    printf("Hello from process!\\n");
}

void kernel_init() {
    printf("Kernel initialized.\\n");
    for (int i = 0; i < NUM_PROCESSES; i++) {
        add_process(i, entry_point);
    }
    set_process_state(0, PROCESS_RUNNING);
}

int main() {
    kernel_init();
    while (1) {
        schedule();
        sleep(1);  // Sleep for 1 second
    }
    return 0;
}
EOL

# Create and populate scheduler.c
cat <<EOL > "${PROJECT_DIR}/src/kernel/scheduler.c"
#include <stdio.h>
#include "scheduler.h"
#include "memory.h"

Process process_table[MAX_PROCESSES];
int process_count = 0;

void add_process(int pid, void (*entry_point)(void)) {
    if (process_count < MAX_PROCESSES) {
        process_table[process_count].pid = pid;
        process_table[process_count].state = PROCESS_RUNNING;
        process_table[process_count].entry_point = entry_point;
        process_count++;
    }
}

void set_process_state(int pid, ProcessState state) {
    for (int i = 0; i < process_count; i++) {
        if (process_table[i].pid == pid) {
            process_table[i].state = state;
            break;
        }
    }
}

void schedule() {
    int next_process = -1;
    for (int i = 0; i < process_count; i++) {
        if (process_table[i].state == PROCESS_RUNNING &&
            (next_process == -1 || process_table[i].pid < process_table[next_process].pid)) {
            next_process = i;
        }
    }
    if (next_process != -1) {
        printf("Scheduling process %d...\\n", process_table[next_process].pid);
        process_table[next_process].entry_point();
        set_process_state(process_table[next_process].pid, PROCESS_TERMINATED);
    }
}
EOL

# Create and populate memory.c
cat <<EOL > "${PROJECT_DIR}/src/kernel/memory.c"
#include "memory.h"
#include <stdlib.h>

void* allocate_memory(size_t size) {
    return calloc(1, size);
}

void free_memory(void* ptr) {
    free(ptr);
}
EOL

# Create and populate scheduler.h
cat <<EOL > "${PROJECT_DIR}/src/kernel/scheduler.h"
#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <stdbool.h>

#define MAX_PROCESSES 10

typedef enum {
    PROCESS_RUNNING,
    PROCESS_WAITING,
    PROCESS_TERMINATED
} ProcessState;

typedef struct {
    int pid;
    ProcessState state;
    void (*entry_point)(void);
} Process;

extern Process process_table[MAX_PROCESSES];
extern int process_count;

void add_process(int pid, void (*entry_point)(void));
void set_process_state(int pid, ProcessState state);
void schedule();

#endif // SCHEDULER_H
EOL

# Create and populate memory.h
cat <<EOL > "${PROJECT_DIR}/src/kernel/memory.h"
#ifndef MEMORY_H
#define MEMORY_H

#include <stddef.h>

void* allocate_memory(size_t size);
void free_memory(void* ptr);

#endif // MEMORY_H
EOL

# Create and populate kernel.h
cat <<EOL > "${PROJECT_DIR}/src/kernel/kernel.h"
#ifndef KERNEL_H
#define KERNEL_H

#include <stdint.h>

void kernel_init();
void kernel_main();
void kernel_panic(const char* message, uint32_t code);

#endif // KERNEL_H
EOL

# Create and populate Makefile
cat <<EOL > "${PROJECT_DIR}/Makefile"
# Makefile for Dareu Kaengi Microkernel

# Compiler
CC = gcc

# Source directories
SRC_DIR = src
KERNEL_DIR = \$(SRC_DIR)/kernel

# Output directory
BUILD_DIR = build

# Compiler flags
CFLAGS = -Wall -Wextra -I\$(KERNEL_DIR)

# Targets
all: \$(BUILD_DIR)/kernel

\$(BUILD_DIR)/kernel: \$(KERNEL_DIR)/kernel.o \$(KERNEL_DIR)/scheduler.o \$(KERNEL_DIR)/memory.o
\t\$(CC) -o \$@ \$^

\$(KERNEL_DIR)/%.o: \$(KERNEL_DIR)/%.c
\t\$(CC) \$(CFLAGS) -c \$< -o \$@

clean:
\trm -rf \$(BUILD_DIR)/*.o \$(KERNEL_DIR)/*.o \$(BUILD_DIR)/kernel
EOL

# Create and populate README.md
cat <<EOL > "${PROJECT_DIR}/README.md"
# Dareu Kaengi Microkernel

Dareu Kaengi is a microkernel designed for Intel Alder Lake-U chipsets, focusing on modularity, performance, and security.

## Project Structure
- **src/**: Contains the source code for the kernel, drivers, and modules.
- **build/**: Output directory for compiled binaries.

## Build Instructions
To build the kernel, run:
\`\`\`
make
\`\`\`

To clean the build files, run:
\`\`\`
make clean
\`\`\`
EOL

echo "Setup complete!"

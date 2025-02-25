#include <stdio.h>
#include <unistd.h>
#include "kernel.h"
#include <stdio.h>
#include <stdarg.h>

void my_printf(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);
}

uint32_t get_process_id() {
    // Implement or mock this function
    return 1;
}

void memory_init() {
    // Implement memory initialization
}

void scheduler_init() {
    // Implement scheduler initialization
}
#include "memory.h"
#include "scheduler.h"
#include "ipc.h"
#include "network.h"
#include "interrupts.h"
#include "ai.h"
#include "module.h"

#define NUM_PROCESSES 5

void entry_point(void) {
    printf("Hello from process!\n");
}

void kernel_init() {
    printf("Kernel initialized.\n");

    // Initialize essential services
    printf("Initializing IPC...\n");
    init_ipc();
    printf("IPC initialized.\n");

    printf("Initializing network support...\n");
    init_network();
    printf("Network support initialized.\n");

    printf("Initializing memory management...\n");
    init_memory_management();
    printf("Memory management initialized.\n");

    printf("Initializing interrupt handling...\n");
    init_interrupts();
    printf("Interrupt handling initialized.\n");

    printf("Initializing AI...\n");
    init_ai();
    printf("AI initialized.\n");

    // Initialize modules
    printf("Initializing modules...\n");
    init_module("example_module");
    printf("Modules initialized.\n");

    // Initialize task scheduling
    printf("Initializing task scheduler...\n");
    init_scheduler();
    printf("Task scheduler initialized.\n");

    for (int i = 0; i < NUM_PROCESSES; i++) {
        printf("Adding process %d...\n", i);
        add_process(i, entry_point, 1); // Assuming priority 1 for all processes
    }
    set_process_state(0, PROCESS_RUNNING);
    printf("Kernel initialization complete.\n");
}

int main() {
    kernel_init();
    while (1) {
        schedule();
        sleep(1);  // Sleep for 1 second
    }
    return 0;
}

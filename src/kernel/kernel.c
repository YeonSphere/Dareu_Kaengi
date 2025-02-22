#include <stdio.h>
#include <unistd.h>
#include "kernel.h"
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
    init_ipc();
    init_network();
    init_memory_management();
    init_interrupts();
    init_ai();

    // Initialize modules
    init_module("example_module");

    // Initialize task scheduling
    init_scheduler();

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

#include <stdio.h>
#include "scheduler.h"
#include "memory.h"

#define MAX_PROCESSES 100

typedef enum {
    PROCESS_RUNNING,
    PROCESS_WAITING,
    PROCESS_TERMINATED
} ProcessState;

typedef struct {
    int pid;
    ProcessState state;
    void (*entry_point)(void);
    int priority;
} Process;

Process process_table[MAX_PROCESSES];
int process_count = 0;

void add_process(int pid, void (*entry_point)(void), int priority) {
    if (process_count < MAX_PROCESSES) {
        process_table[process_count].pid = pid;
        process_table[process_count].state = PROCESS_RUNNING;
        process_table[process_count].entry_point = entry_point;
        process_table[process_count].priority = priority;
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
            (next_process == -1 || process_table[i].priority > process_table[next_process].priority)) {
            next_process = i;
        }
    }
    if (next_process != -1) {
        printf("Scheduling process %d...\n", process_table[next_process].pid);
        process_table[next_process].entry_point();
        set_process_state(process_table[next_process].pid, PROCESS_TERMINATED);
    }
}

void init_scheduler() {
    printf("Task scheduler initialized.\n");
    // Implement scheduler initialization logic here
}

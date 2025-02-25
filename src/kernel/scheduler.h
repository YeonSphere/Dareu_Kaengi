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
    void (*entry_point)(void);
    ProcessState state;
    int priority;
} Process;

extern Process process_table[MAX_PROCESSES];
extern int process_count;

void add_process(int pid, void (*entry_point)(void), int priority);
void set_process_state(int pid, ProcessState state);
void schedule();
void init_scheduler();

#endif // SCHEDULER_H

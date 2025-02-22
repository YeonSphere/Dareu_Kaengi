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

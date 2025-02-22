#ifndef SCHEDULER_H
#define SCHEDULER_H

// Function prototypes for scheduler
void add_process(int id, void (*entry_point)(void));
void set_process_state(int id, int state);
void schedule();
void init_scheduler();

#endif // SCHEDULER_H

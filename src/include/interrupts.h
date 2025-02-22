#ifndef INTERRUPTS_H
#define INTERRUPTS_H

// Function prototypes for interrupt handling
void init_interrupts();
void setup_idt();
void enable_interrupts();
void handle_interrupt(int interrupt_number);

#endif // INTERRUPTS_H

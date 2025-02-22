#ifndef KERNEL_H
#define KERNEL_H

#include <stdint.h>

void kernel_init();
void kernel_main();
void kernel_panic(const char* message, uint32_t code);

#endif // KERNEL_H

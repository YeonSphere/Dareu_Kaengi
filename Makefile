# Makefile for Dareu Kaengi Microkernel

# Compiler
CC = gcc

# Source directories
SRC_DIR = src
KERNEL_DIR = $(SRC_DIR)/kernel
INCLUDE_DIR = $(SRC_DIR)/include

# Output directory
BUILD_DIR = build

# Compiler flags
CFLAGS = -Wall -Wextra -I$(INCLUDE_DIR)

# Targets
all: $(BUILD_DIR)/kernel

$(BUILD_DIR)/kernel: $(KERNEL_DIR)/kernel.o $(KERNEL_DIR)/scheduler.o $(KERNEL_DIR)/memory.o $(KERNEL_DIR)/ipc.o $(KERNEL_DIR)/network.o $(KERNEL_DIR)/interrupts.o $(KERNEL_DIR)/ai.o $(KERNEL_DIR)/module.o
	$(CC) -o $@ $^

$(KERNEL_DIR)/%.o: $(KERNEL_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(BUILD_DIR)/*.o $(KERNEL_DIR)/*.o $(BUILD_DIR)/kernel

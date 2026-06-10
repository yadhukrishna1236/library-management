# Library Management System Makefile
# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -g -std=c99
TARGET = library_system

# Source files
SRCS = main.c book.c hash.c queue.c stack.c file_handler.c
OBJS = $(SRCS:.c=.o)

# Default target
all: $(TARGET)

# Link executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Compile source files to object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean build files
clean:
	rm -f $(OBJS) $(TARGET) library.dat

# Rebuild from scratch
rebuild: clean all

# Run the program
run: $(TARGET)
	./$(TARGET)

# Phony targets (not actual files)
.PHONY: all clean rebuild run
.PHONY: clean tidy

# Compiler and flags
CC=gcc
CFLAGS=-Wall -std=gnu99 -g
LFLAGS=-lm

# Directories
BUILD_DIR=./build/
SRC_DIR=./src/

# Source and header files
HDR=$(wildcard $(SRC_DIR)*.h)
SRC=$(filter-out $(SRC_DIR)*_test.c, $(wildcard $(SRC_DIR)*.c))
OBJ=$(patsubst $(SRC_DIR)%.c,$(BUILD_DIR)%.o,$(SRC))

# Test flags and files
CFLAGS_TEST=$(CFLAGS)
LFLAGS_TEST=$(LFLAGS) -lcheck -lm -lpthread -lrt -lsubunit
SRC_TEST=$(wildcard $(SRC_DIR)*_test.c)
OBJ_TEST=$(patsubst $(SRC_DIR)%.c,$(BUILD_DIR)%.o,$(SRC_TEST))

# Default target
all: main

# Main executable
main: $(OBJ)
	$(CC) $(CFLAGS) -o $(BUILD_DIR)tree $(OBJ) $(LFLAGS)

# Test executable
test: $(OBJ_TEST)
	$(CC) $(CFLAGS_TEST) -o $(BUILD_DIR)test $(OBJ_TEST) $(LFLAGS_TEST)

# Rule for building object files
$(BUILD_DIR)%.o: $(SRC_DIR)%.c $(HDR)
	mkdir -p $(BUILD_DIR)
	$(CC) -c $(CFLAGS) -o $@ $<

# Clean up all generated files
clean:
	rm -rf $(BUILD_DIR)

# Tidy intermediate files
tidy:
	rm -rf $(BUILD_DIR)*.o

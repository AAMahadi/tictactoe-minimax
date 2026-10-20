# Compiler and Flags
CC ?= gcc
CFLAGS = -Wall -Wextra -std=c99 -Iinclude -Iexternal/raylib/src

# Directories and Target
SRC_DIR = src
BUILD_DIR = build
TARGET = $(BUILD_DIR)/tictactoe

# Find all .c files in src/ automatically
SRCS = $(wildcard $(SRC_DIR)/*.c)
# Convert src/filename.c to build/filename.o
OBJS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))

# Raylib Submodule Directory
RAYLIB_DIR = external/raylib/src
RAYLIB_LIB = $(RAYLIB_DIR)/libraylib.a

# OS Detection for Raylib dependencies
ifeq ($(OS),Windows_NT)
    LDLIBS = -lraylib -lopengl32 -lgdi32 -lwinmm
else
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Linux)
        LDLIBS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
    endif
    ifeq ($(UNAME_S),Darwin)
        LDLIBS = -lraylib -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo
    endif
endif

LDFLAGS = -L$(RAYLIB_DIR)

# Default target
all: $(TARGET)

# Link all compiled .o files into the final executable
$(TARGET): $(RAYLIB_LIB) $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) $(LDLIBS) -o $@

# Compile each .c file separately into an object file (.o)
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Create the build output directory
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Build Raylib static library inside external/raylib if not built yet
$(RAYLIB_LIB):
	$(MAKE) -C $(RAYLIB_DIR)

# Run the compiled game
run: $(TARGET)
	./$(TARGET)

# Clean up build artifacts
clean:
	rm -rf $(BUILD_DIR)
	$(MAKE) -C $(RAYLIB_DIR) clean

.PHONY: all run clean
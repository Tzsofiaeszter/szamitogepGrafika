CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -Iinclude
BUILD_DIR = obj
SRC_DIR = src
EXECUTABLE = game

# List all your source files here
SOURCES = $(wildcard $(SRC_DIR)/*.c)

# Create object files from source files
OBJECTS = $(SOURCES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

LDLIBS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lopengl32 -lm

all: $(BUILD_DIR) $(EXECUTABLE)

$(BUILD_DIR):
	mkdir -p $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@ $(LDLIBS)

run: $(EXECUTABLE)
	./$(EXECUTABLE)

clean:
	rm -rf $(BUILD_DIR) $(EXECUTABLE);
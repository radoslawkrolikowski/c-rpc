CC ?= gcc

SRC_DIR = ./src
TEST_DIR = ./tests
BUILD_DIR = ./bin
NAME = app.elf

# Search for header files
CFLAGS += -I$(SRC_DIR)/serialize

# List source files
CSOURCES = $(SRC_DIR)/main.c
CSOURCES += $(wildcard $(SRC_DIR)/serialize/*.c)

# Compiler flags
CFLAGS += -Wall

# Linker flags
LDFLAGS +=

# Generate names for output object files
COBJECTS = $(patsubst %.c, %.o, $(CSOURCES))

# Default rule: build application
.PHONY: all
all: $(NAME)

# Build components
$(COBJECTS) : %.o : %.c
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Build the target application
.PHONY: $(NAME)
$(NAME): $(COBJECTS)
	$(CC) $(COBJECTS) -o $(BUILD_DIR)/$(NAME) $(LDFLAGS)

# Remove object files
.PHONY: clean
clean:
	rm -f $(COBJECTS)

# Run tests
.PHONY: test
test:
	make -C $(TEST_DIR)

# Clean tests
.PHONY: test_clean
test_clean:
	make -C $(TEST_DIR) clean

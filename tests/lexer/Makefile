COMPONENT_NAME = lexer

# Dynamically generate absolute paths
MAKEFILE_DIR = $(dir $(realpath $(firstword $(MAKEFILE_LIST))))
PROJECT_DIR = $(realpath $(MAKEFILE_DIR)../..)
SRC_DIR = $(PROJECT_DIR)/src
TEST_DIR = $(PROJECT_DIR)/tests

CPPUTEST_HOME ?= $(PROJECT_DIR)/tools/cpputest

INCLUDE_DIRS = $(SRC_DIR)/$(COMPONENT_NAME)
SRC_DIRS = $(SRC_DIR)/$(COMPONENT_NAME)

# Includes CppUTest header files
INCLUDE_DIRS += $(CPPUTEST_HOME)/include

TEST_SRC_DIRS = $(TEST_DIR)/$(COMPONENT_NAME)

# Run MakefileWorker.mk
include $(CPPUTEST_HOME)/build/MakefileWorker.mk

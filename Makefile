# Compiler
CXX = g++
# Compiler flags
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic -Iinclude

# Linker flags
ifeq ($(OS),Windows_NT)
	LDFLAGS = -lstdc++fs
else
	LDFLAGS = -stdlib=libc++
endif
# Target executable
TARGET = main_example

# Source directories
SRC_DIR = src/cc_bitcask
EXAMPLE_DIR = example

# Source files
SRC_FILES = $(wildcard $(SRC_DIR)/*.cc)
EXAMPLE_FILE = $(wildcard $(EXAMPLE_DIR)/*.cc)

# Object files
OBJS = $(patsubst %.cc, %.o, $(SRC_FILES))

# Default target
all: $(TARGET)

# Build target executable
$(TARGET): $(OBJS) $(EXAMPLE_FILE)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Compile source files to object files
%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build artifacts
clean:
	rm -f $(TARGET) $(OBJS)

fmt:
	find . -name "*.cc" -o -name "*.hpp" | xargs clang-format -i

# Phony targets
.PHONY: all clean

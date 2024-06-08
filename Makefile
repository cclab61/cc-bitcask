# Compiler
CXX = g++
# Compiler flags
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic -Iinclude -I/opt/homebrew/Cellar/googletest/1.14.0/include

# Linker flags
ifeq ($(OS),Windows_NT)
	LDFLAGS = -lstdc++fs -L/opt/homebrew/Cellar/googletest/1.14.0/lib -lgtest -lgtest_main -lpthread
else
	LDFLAGS = -stdlib=libc++ -L/opt/homebrew/Cellar/googletest/1.14.0/lib -lgtest -lgtest_main -lpthread
endif
# Target executable
TARGET = main_example
TEST_TARGET = run_tests

# Source directories
SRC_DIR = src/cc_bitcask
EXAMPLE_DIR = example
TEST_DIR = test

# Source files
SRC_FILES = $(wildcard $(SRC_DIR)/*.cc)
EXAMPLE_FILE = $(wildcard $(EXAMPLE_DIR)/*.cc)

# Test file
TEST_FILES = $(wildcard $(TEST_DIR)/*.cc)

# Object files
OBJS = $(patsubst %.cc, %.o, $(SRC_FILES))
TEST_OBJS = $(patsubst %.cc, %.o, $(TEST_FILES))

# Default target
all: $(TARGET) $(TEST_TARGET)

# Build target executable
$(TARGET): $(OBJS) $(EXAMPLE_FILE)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

$(TEST_TARGET): $(OBJS) $(TEST_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Compile source files to object files
%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build artifacts
clean:
	rm -f $(TARGET) $(OBJS) $(TEST_TARGET) $(TEST_OBJS)
	rm -r ./testdir

fmt:
	find . -name "*.cc" -o -name "*.hpp" | xargs clang-format -i

# Phony targets
.PHONY: all clean

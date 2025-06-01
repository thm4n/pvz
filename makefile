# Compiler and flags
CXX := g++
CXXFLAGS := -Wall -Wextra -std=c++23  
CXXINCS := -Isource $(shell sdl2-config --cflags)
CXXLIBS := -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
CXXDBG := -g3 -fsanitize=address -static-libasan
CXXARGS := $(CXXFLAGS) $(CXXINCS) $(CXXDBG)


SRC_DIR := source/src
OBJ_DIR := bin

# Find all .cpp files in the 'source' directory
SRC := $(shell find source -name '*.cpp')
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
_OBJ := $(SRC:.cpp=.o)
OBJ := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))


# Output binary name
TARGET := pvz

.PHONY: $(TARGET)

# Default target
all: $(OBJ_DIR) $(TARGET)

$(OBJ_DIR):
	mkdir -p $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@echo "compiling $@"
	$(CXX) $(CXXARGS) -c $^ -o $@

# Link all source files into the target
$(TARGET): $(OBJ)
	@echo "compiling $(TARGET)"
	$(CXX) $(CXXARGS) $(CXXLIBS) -o $@ $^

# Clean build artifacts
clean:
	rm -rf ./bin/*
	rm -f $(TARGET)

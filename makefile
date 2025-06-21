# Compiler and flags
CXX := g++
CXXFLAGS := -Wall -Wextra -std=c++23  
CXXINCS := -Isource $(shell sdl2-config --cflags) -I/usr/local/include
CXXLIBS := -L/usr/local/lib -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -ltinyxml2
CXXDBG := -g3 -fsanitize=address -static-libasan
CXXARGS := $(CXXFLAGS) $(CXXINCS) $(CXXDBG)

DEPENDENCIES := 


SRC_DIR := source/src
OBJ_DIR := bin

# Find all .cpp files in the 'source' directory
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJ := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))


# Output binary name
TARGET := pvz
# List of tests
TESTS := TestAnimationReader TestResourceManager

.PHONY: $(TARGET) $(TESTS)

# Default target
all: $(OBJ_DIR) $(TARGET) $(TESTS)

$(OBJ_DIR):
	mkdir -p $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@echo "compiling $@"
	$(CXX) -c $^ -o $@ $(CXXARGS)

# Link all source files into the target
$(TARGET): $(OBJ)
	@echo "compiling $(TARGET)"
	$(CXX) ./source/entrypoints/main.cpp -o $@ $^ $(CXXARGS) $(CXXLIBS) 

# Clean build artifacts
clean:
	rm -rf ./bin/*
	rm -f $(TARGET) $(TESTS)

TestAnimationReader: $(OBJ)
	$(CXX) ./source/entrypoints/TestAnimationReader.cpp $^ -o $@ $(CXXARGS) $(CXXLIBS)

TestResourceManager: $(OBJ)
	$(CXX) ./source/entrypoints/TestResourceManager.cpp $^ -o $@ $(CXXARGS) $(CXXLIBS)
	
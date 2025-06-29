# Compiler and flags
CXX := g++
CXXWARNINGS := -Wno-switch
CXXFLAGS := -Wall -Wextra -std=c++23 $(CXXWARNINGS)
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
TESTS := TestAnimationReader TestResourceManager TestResourceJson TestFont

.PHONY: $(TARGET) $(TESTS)

# Default target
all: $(OBJ_DIR) $(TARGET) $(TESTS)

$(OBJ_DIR):
	mkdir -p $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@echo "compiling $@"
	$(CXX) -c $^ -o $@ $(CXXARGS)
	@echo ""

# Link all source files into the target
$(TARGET): $(OBJ)
	@echo "compiling $(TARGET)"
	$(CXX) ./source/entrypoints/main.cpp -o $@ $^ $(CXXARGS) $(CXXLIBS)
	@echo ""

# Clean build artifacts
clean:
	rm -rf ./bin/*
	rm -f $(TARGET) $(TESTS)

TestAnimationReader: $(OBJ)
	@echo "compiling $@"
	$(CXX) ./source/entrypoints/TestAnimationReader.cpp $^ -o $@ $(CXXARGS) $(CXXLIBS)
	@echo ""

TestResourceManager: $(OBJ)
	@echo "compiling $@"
	$(CXX) ./source/entrypoints/TestResourceManager.cpp $^ -o $@ $(CXXARGS) $(CXXLIBS)
	@echo ""
	
TestResourceJson: $(OBJ)
	@echo "compiling $@"
	$(CXX) ./source/entrypoints/TestResourceJson.cpp $^ -o $@ $(CXXARGS) $(CXXLIBS)
	@echo ""
	
TestFont: $(OBJ)
	@echo "compiling $@"
	$(CXX) ./source/entrypoints/TestFont.cpp $^ -o $@ $(CXXARGS) $(CXXLIBS)
	@echo ""
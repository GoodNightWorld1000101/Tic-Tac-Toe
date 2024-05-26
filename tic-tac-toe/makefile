# Variables
CXX = g++
CXXFLAGS = -O2 -Wall -Wno-missing-braces
INCLUDES = -I include
LIBS = -L lib -lraylib -lopengl32 -lgdi32 -lwinmm
SRC_DIR = src
OBJ_DIR = build
TARGET = $(OBJ_DIR)/Game.exe

# Collect all .cpp files in the src directory
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
# Generate object files names based on source files
OBJECTS = $(SOURCES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)


# Default target
all: $(TARGET)

# Link object files to create the executable
$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET) $(LIBS)

# Compile each .cpp file to an .o file
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Clean up build artifacts
clean:
	rm -rf $(OBJ_DIR)/*.o $(TARGET)

# Phony targets are not actual files
run: $(TARGET)
	cd $(OBJ_DIR) && ./Game.exe
.PHONY: all clean

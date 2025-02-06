# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -std=c++11

# Include directories
INCLUDES = -I./include -I./src/demos/fireworks

# Source files
SRCS = $(wildcard src/*.cpp src/demos/**/*.cpp)

# Object files
OBJS = $(SRCS:.cpp=.o)

# Executable
EXEC = cyclone

# Default target
all: $(EXEC)

# Link the executable
$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ -lglut -lGLEW -lGL 

# Compile source files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJS) $(EXEC)

.PHONY: all clean

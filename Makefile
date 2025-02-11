# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -std=c++11

# Include directories
INCLUDES = -I./include 

# Source files (recursive search for .cpp files)
SRCS = $(shell find src -type f -name "*.cpp")

# Object files (convert src/xxx.cpp to obj/xxx.o if desired, here simple replacement)
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

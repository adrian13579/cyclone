cmake_minimum_required(VERSION 3.10)
project(cyclone)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add debug flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -g")

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/include)

# Recursively find all source files from the src folder
file(GLOB_RECURSE SOURCES "${PROJECT_SOURCE_DIR}/src/*.cpp")

# Create the executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Find and link OpenGL, GLUT and GLEW libraries
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(GLEW REQUIRED)

target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} ${GLEW_LIBRARY} -g)

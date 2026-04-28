# Minimal CMake version required
cmake_minimum_required(VERSION 3.10)

# Project name
project(ImageFilters)

# Set C++ standard to C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find OpenCV library
find_package(OpenCV REQUIRED)

# Include OpenCV headers
include_directories(${OpenCV_INCLUDE_DIRS})

# Create executable from source files
add_executable(image_filters 
    main.cpp
    filters.cpp
)

# Link OpenCV libraries
target_link_libraries(image_filters ${OpenCV_LIBS})
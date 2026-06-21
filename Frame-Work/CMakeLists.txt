cmake_minimum_required(VERSION 3.10.0)
project(Frame-Work VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(Frame-Work STATIC
    src/logging.cpp include/core.h include/logging.h src/assert.cpp include/assert.h
)


target_include_directories(Frame-Work
    PUBLIC
        include
)

find_package(glfw3 REQUIRED)


target_link_libraries(Frame-Work
    PUBLIC
        glfw
)
message(STATUS "GLFW FOUND")
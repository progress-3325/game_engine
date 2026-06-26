cmake_minimum_required(VERSION 3.10.0)
project(Frame-Work VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(Frame-Work STATIC
    src/cs_logging.cpp include/core.h include/cs_logging.h src/cs_assert.cpp include/cs_assert.h 
    src/cs_time.cpp include/cs_time.h src/cs_filesystem.cpp include/cs_filesystem.h
    
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
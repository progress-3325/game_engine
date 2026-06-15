cmake_minimum_required(VERSION 3.10.0)
project(GameEngine VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(Frame-Work)
add_subdirectory(Editor)

target_include_directories(Frame-Work
    PUBLIC
        include
)
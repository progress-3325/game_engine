cmake_minimum_required(VERSION 3.10.0)
project(Editor VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Editor
    src/main.cpp src/application.cpp include/application.h src/window.cpp include/window.h
)


target_include_directories(Editor
    PUBLIC
        include
        ../Frame-Work/include
)

find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)

target_link_libraries(Editor
    PRIVATE
        Frame-Work
        glfw
        OpenGL::GL
)
cmake_minimum_required(VERSION 3.27)

project(triangle)

add_executable(triangle main.cpp)

include_directories(../../glad/include)

target_link_libraries(triangle glfw OpenGL::GL glad)
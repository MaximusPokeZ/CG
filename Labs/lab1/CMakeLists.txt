cmake_minimum_required(VERSION 3.27)

project(circle)

add_executable(circle circle.cpp)

include_directories(../glad/include)

target_link_libraries(circle sfml-system sfml-window sfml-graphics sfml-audio sfml-network glfw OpenGL::GL glad)
cmake_minimum_required(VERSION 3.27)

add_executable(scene main.cpp)

include_directories(../include)

target_link_libraries(scene sfml-system sfml-window sfml-graphics glfw OpenGL::GL glad)

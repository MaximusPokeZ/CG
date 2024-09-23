cmake_minimum_required(VERSION 3.27)
project(window)

add_executable(window main.cpp)



target_link_libraries(window sfml-system sfml-window sfml-graphics sfml-audio sfml-network glfw OpenGL::GL glad)

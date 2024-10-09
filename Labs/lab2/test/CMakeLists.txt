cmake_minimum_required(VERSION 3.27)

add_executable(scene main.cpp)

include_directories(../include)

target_link_libraries(scene shape Window sfml-system sfml-window sfml-graphics glfw OpenGL::GL glad Qt6::Widgets Qt6::OpenGL)


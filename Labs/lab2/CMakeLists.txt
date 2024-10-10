cmake_minimum_required(VERSION 3.27)

add_subdirectory(test)

add_library(shape src/Shape.cpp)
add_library(Window src/Window.cpp)

target_include_directories(
        shape
        PUBLIC
        ./include
)

target_include_directories(
        Window
        PUBLIC
        ./include
)

target_link_libraries(shape glfw OpenGL::GL Qt6::Widgets Qt6::OpenGL)
target_link_libraries(Window glm::glm sfml-system sfml-window sfml-graphics sfml-audio sfml-network glfw OpenGL::GL Qt6::Widgets Qt6::OpenGL)

include_directories(../glad/include)


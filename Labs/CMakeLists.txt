cmake_minimum_required(VERSION 3.27)
project(Labs)

set(CMAKE_CXX_STANDARD 23)

# Подавляем предупреждения о депрекации OpenGL в macOS
add_definitions(-DGL_SILENCE_DEPRECATION)

find_package(SFML 2.5 COMPONENTS system window graphics audio network REQUIRED)

find_package(glfw3 3.3 REQUIRED)

find_package(OpenGL REQUIRED)

find_package(Qt6 REQUIRED Widgets OpenGL REQUIRED)

# find_package(GLUT REQUIRED)

include_directories(${SFML_INCLUDE_DIRS})
include_directories(${OPENGL_INCLUDE_DIR})
include_directories(${GLFW_INCLUDE_DIRS})
# include_directories(${GLUT_INCLUDE_DIRS})

add_library(glad STATIC glad/src/glad.c)
include_directories(glad/include)

add_subdirectory(Tests/window)
add_subdirectory(Tests/Triangle)
add_subdirectory(lab1)
add_subdirectory(lab2)


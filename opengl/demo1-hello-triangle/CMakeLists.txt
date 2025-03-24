cmake_minimum_required(VERSION 3.16)
project(opengl-demo)                                          #必须

add_executable(opengl-demo glad/src/glad.c
                           ./hello-triangle.cpp)                     #通常父目录(二选一)

include_directories(./glad/include)                              #必须

target_link_libraries(opengl-demo GL GLU glut glfw dl)       #必须

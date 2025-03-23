cmake_minimum_required(VERSION 3.16)
project(opengl-demo)                                          #必须

#add_subdirectory(opengl-demo)                         #父目录必须，子目录不必

#add_library(库文件名称 STATIC 文件)                    #通常子目录(二选一)

add_executable(opengl-demo glad/src/glad.c
                           ./hello-triangle.cpp)                     #通常父目录(二选一)

include_directories(./glad/include)                              #必须

link_directories(./)                                 #必须

target_link_libraries(opengl-demo GL GLU glut glfw dl)       #必须

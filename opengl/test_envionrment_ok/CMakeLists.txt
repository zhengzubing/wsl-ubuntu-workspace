cmake_minimum_required(VERSION 3.16)
project(opengl_demo)                                          #必须

# 如果包未安装，则使用 APT 进行安装
execute_process(
    COMMAND sudo apt install -y freeglut3-dev libglfw3-dev libc6-dev
)

add_executable(opengl_demo ./opengl_demo.cpp)                     #通常父目录(二选一)

include_directories(./)                              #必须

link_directories(./)                                 #必须

target_link_libraries(opengl_demo GL GLU glut)       #必须

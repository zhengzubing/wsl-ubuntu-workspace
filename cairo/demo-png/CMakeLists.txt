cmake_minimum_required(VERSION 3.16)
project(demo-png)                                          #必须

execute_process(
    COMMAND sudo apt install libcairo2 libcairo2-dev
)

add_executable(demo-png ./hello_world.cpp)                     #通常父目录(二选一)

include_directories(/usr/include/cairo
    /usr/include/libpng16
    /usr/include/freetype2
    /usr/include/pixman-1
)                              #必须

link_directories(./)                                 #必须

target_link_libraries(demo-png cairo)       #必须

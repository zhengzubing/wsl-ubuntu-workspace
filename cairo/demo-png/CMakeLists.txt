cmake_minimum_required(VERSION 3.28)
project(demo-png)                                          #必须

#add_subdirectory(demo-png)                         #父目录必须，子目录不必

#add_library(库文件名称 STATIC 文件)                    #通常子目录(二选一)

add_executable(demo-png ./cairo-demo.cpp)                     #通常父目录(二选一)

include_directories(/usr/include/cairo
    /usr/include/libpng16
    /usr/include/freetype2
    /usr/include/pixman-1
)                              #必须

link_directories(./)                                 #必须

target_link_libraries(demo-png cairo)       #必须

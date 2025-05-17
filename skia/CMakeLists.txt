cmake_minimum_required(VERSION 3.28)
project(skia_demo)                                          #必须


#add_subdirectory(skia_demo)                         #父目录必须，子目录不必

include_directories(./third_party/skia_lib/libskia
                    ./third_party/skia_lib/libskia/include/atlastext/
                    ./third_party/skia_lib/libskia/include/c/
                    ./third_party/skia_lib/libskia/include/codec/
                    ./third_party/skia_lib/libskia/include/compute/
                    ./third_party/skia_lib/libskia/include/config/
                    ./third_party/skia_lib/libskia/include/core/
                    ./third_party/skia_lib/libskia/include/effects/
                    ./third_party/skia_lib/libskia/include/encode/
                    ./third_party/skia_lib/libskia/include/gpu/
                    ./third_party/skia_lib/libskia/include/image/
                    ./third_party/skia_lib/libskia/include/images/
                    ./third_party/skia_lib/libskia/include/jumper/
                    ./third_party/skia_lib/libskia/include/lazy/
                    ./third_party/skia_lib/libskia/include/opts/
                    ./third_party/skia_lib/libskia/include/pathops/
                    ./third_party/skia_lib/libskia/include/pdf/
                    ./third_party/skia_lib/libskia/include/pipe/
                    ./third_party/skia_lib/libskia/include/ports/
                    ./third_party/skia_lib/libskia/include/private/
                    ./third_party/skia_lib/libskia/include/sfnt/
                    ./third_party/skia_lib/libskia/include/shaders/
                    ./third_party/skia_lib/libskia/include/sksl/
                    ./third_party/skia_lib/libskia/include/svg/
                    ./third_party/skia_lib/libskia/include/utils/
                    ./third_party/skia_lib/libskia/include/xml/
                    ./third_party/skia_lib/libskia/include/xps/
                    )                              #必须

# export C_INCLUDE_PATH=/home/zhengzubing/wsl-ubuntu-workspace/skia/third_party/skia_lib/libskia:$C_INCLUDE_PATH 
# export CPLUS_INCLUDE_PATH=/home/zhengzubing/wsl-ubuntu-workspace/skia/third_party/skia_lib/libskia:$CPLUS_INCLUDE_PATH 

# export LD_LIBRARY_PATH=/home/zhengzubing/wsl-ubuntu-workspace/skia/third_party/skia_lib/libskia/lib/linux/x64/Shared:$LD_LIBRARY_PATH
# export LIBRARY_PATH=/home/zhengzubing/wsl-ubuntu-workspace/skia/third_party/skia_lib/libskia/lib/linux/x64/Static:$LIBRARY_PATH   #静态链接库搜索路径

#add_library(库文件名称 STATIC 文件)                    #通常子目录(二选一)

add_executable(skia_demo ./skia_demo.cpp)                     #通常父目录(二选一)

# link_directories(./third_party/skia_lib/libskia/lib/linux/x64/Static)                                 #必须
link_directories(./third_party/skia_lib/libskia/lib/linux/x64/Shared)                                 #必须

# target_link_libraries(skia_demo skia sksg)       #必须
target_link_libraries(skia_demo libskia.so)       #必须

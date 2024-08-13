cmake_minimum_required(VERSION 3.28)
project(skia-demo)                                          #必须


#add_subdirectory(skia-demo)                         #父目录必须，子目录不必

include_directories(./third-party/skia-lib/libskia
                    ./third-party/skia-lib/libskia/include/atlastext/
                    ./third-party/skia-lib/libskia/include/c/
                    ./third-party/skia-lib/libskia/include/codec/
                    ./third-party/skia-lib/libskia/include/compute/
                    ./third-party/skia-lib/libskia/include/config/
                    ./third-party/skia-lib/libskia/include/core/
                    ./third-party/skia-lib/libskia/include/effects/
                    ./third-party/skia-lib/libskia/include/encode/
                    ./third-party/skia-lib/libskia/include/gpu/
                    ./third-party/skia-lib/libskia/include/image/
                    ./third-party/skia-lib/libskia/include/images/
                    ./third-party/skia-lib/libskia/include/jumper/
                    ./third-party/skia-lib/libskia/include/lazy/
                    ./third-party/skia-lib/libskia/include/opts/
                    ./third-party/skia-lib/libskia/include/pathops/
                    ./third-party/skia-lib/libskia/include/pdf/
                    ./third-party/skia-lib/libskia/include/pipe/
                    ./third-party/skia-lib/libskia/include/ports/
                    ./third-party/skia-lib/libskia/include/private/
                    ./third-party/skia-lib/libskia/include/sfnt/
                    ./third-party/skia-lib/libskia/include/shaders/
                    ./third-party/skia-lib/libskia/include/sksl/
                    ./third-party/skia-lib/libskia/include/svg/
                    ./third-party/skia-lib/libskia/include/utils/
                    ./third-party/skia-lib/libskia/include/xml/
                    ./third-party/skia-lib/libskia/include/xps/
                    )                              #必须

# export C_INCLUDE_PATH=/home/zhengzubing/wsl-ubuntu-workspace/skia/third-party/skia-lib/libskia:$C_INCLUDE_PATH 
# export CPLUS_INCLUDE_PATH=/home/zhengzubing/wsl-ubuntu-workspace/skia/third-party/skia-lib/libskia:$CPLUS_INCLUDE_PATH 

# export LD_LIBRARY_PATH=/home/zhengzubing/wsl-ubuntu-workspace/skia/third-party/skia-lib/libskia/lib/linux/x64/Shared:$LD_LIBRARY_PATH
# export LIBRARY_PATH=/home/zhengzubing/wsl-ubuntu-workspace/skia/third-party/skia-lib/libskia/lib/linux/x64/Static:$LIBRARY_PATH   #静态链接库搜索路径

#add_library(库文件名称 STATIC 文件)                    #通常子目录(二选一)

add_executable(skia-demo ./skia-demo.cpp)                     #通常父目录(二选一)

# link_directories(./third-party/skia-lib/libskia/lib/linux/x64/Static)                                 #必须
link_directories(./third-party/skia-lib/libskia/lib/linux/x64/Shared)                                 #必须

# target_link_libraries(skia-demo skia sksg)       #必须
target_link_libraries(skia-demo libskia.so)       #必须

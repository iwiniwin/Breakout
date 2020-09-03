# cmake最低版本号要求
cmake_minimum_required (VERSION 2.8)

project (Breakout)
set (Breakout_VERSION_MAJOR 1)
set (Breakout_VERSION_MINOR 0)

set (CMAKE_CXX_STAND 11)

# 配置一个头文件来传递一个cmake设置到源代码
configure_file (
    "${PROJECT_SOURCE_DIR}/BreakoutConfig.h.in"
    "${PROJECT_SOURCE_DIR}/BreakoutConfig.h"
)

# 添加头文件搜索路径
# include_directories ("${PROJECT_SOURCE_DIR}")

# 查找当前目录下的所有源文件并存入DIR_SRCS变量
# aux_source_directory(./src DIR_SRCS)

# 添加一个可编译的目标到工程
add_executable (Breakout src/main.cc)

# 生成链接库
# add_library (subdir subdir.cc)

# 添加链接库
# target_link_libraries (Breakout subdir)
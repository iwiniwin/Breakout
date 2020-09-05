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

# 保证subdir被编译
add_subdirectory (3rd/glfw)

# 添加头文件搜索路径
include_directories (3rd/glfw/include)

# 生成链接库
# add_library (glfw 3rd/glfw/src)


include_directories (3rd/glad/include)
add_library (glad 3rd/glad/src/glad.c)

include_directories (3rd/glm/glm)

add_subdirectory (3rd/freetype)
include_directories (3rd/freetype/include)

# 查找当前目录下的所有源文件并存入DIR_SRCS变量
# aux_source_directory(./src DIR_SRCS)

# 添加一个可编译的目标到工程
add_executable (Breakout src/main.cc)

# 添加链接库
target_link_libraries (Breakout glfw glad freetype)

# target_compile_definitions(Breakout PRIVATE GLFW_INCLUDE_NONE)
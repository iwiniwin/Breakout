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

set (3RD_DIR 3rd)

# glfw
set (GLFW_DIR ${3RD_DIR}/glfw)
# 保证glfw dir被编译
add_subdirectory (${GLFW_DIR})
# 添加头文件搜索路径
include_directories (${GLFW_DIR}/include)

# glad
set (GLAD_DIR ${3RD_DIR}/glad)
include_directories (${GLAD_DIR}/include)
# 生成链接库
add_library (glad ${GLAD_DIR}/src/glad.c)

# glm
set (GLM_DIR ${3RD_DIR}/glm)
include_directories (${GLM_DIR}/glm)

# freetype
set (FREETYPE_DIR ${3RD_DIR}/freetype)
add_subdirectory (${FREETYPE_DIR})
include_directories (${FREETYPE_DIR}/include)

# stb_image
set (STB_IMAGE_DIR ${3RD_DIR}/stb_image)
include_directories (${STB_IMAGE_DIR})
add_library (stb_image ${STB_IMAGE_DIR}/stb_image.cc)

# 查找当前目录下的所有源文件并存入DIR_SRCS变量
aux_source_directory(src SRC_DIR)

# 添加一个可编译的目标到工程
add_executable (Breakout ${SRC_DIR})

# 添加链接库
target_link_libraries (Breakout glfw glad freetype stb_image)

# target_compile_definitions(Breakout PRIVATE GLFW_INCLUDE_NONE)
# cmake最低版本号要求
cmake_minimum_required (VERSION 2.8)

set(PROJECT_NAME Breakout)

project (${PROJECT_NAME})
set (${PROJECT_NAME}_VERSION_MAJOR 1)
set (${PROJECT_NAME}_VERSION_MINOR 0)

set (CMAKE_CXX_STAND 11)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# 配置一个头文件来传递一个cmake设置到源代码
configure_file (
    "${PROJECT_SOURCE_DIR}/${PROJECT_NAME}Config.h.in"
    "${PROJECT_SOURCE_DIR}/${PROJECT_NAME}Config.h"
)

set (3RD_DIR ${PROJECT_SOURCE_DIR}/3rd)
set(CMAKE_MODULE_PATH ${3RD_DIR})

# IrrKlang
find_package (IrrKlang REQUIRED)
include_directories (${IRRKLANG_INCLUDE_DIR})

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

# 设置MSVC编译编码
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/source-charset:utf-8>")

# 查找当前目录下的所有源文件并存入DIR_SRCS变量
# aux_source_directory(src SRC_DIR)

# 递归列出所有源文件
file (GLOB_RECURSE SOURCE_FILES *.cc)

# 添加一个可编译的目标到工程
add_executable (${PROJECT_NAME} ${SOURCE_FILES})

# 设置工作目录
# set_property(TARGET ${PROJECT_NAME} PROPERTY VS_DEBUGGER_WORKING_DIRECTORY 
#     ${CMAKE_SOURCE_DIR}/resources
# )

# 添加链接库
target_link_libraries (${PROJECT_NAME} glfw glad freetype stb_image ${IRRKLANG_LIBRARY})

# target_compile_definitions(${PROJECT_NAME} PRIVATE GLFW_INCLUDE_NONE)

# 复制资源文件到工作目录
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/resources
    $<TARGET_FILE_DIR:${PROJECT_NAME}>/resources
)

# 复制库到工作目录
if(WIN32)
    if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC" OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
        add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${IRRKLANG_BIN_DIR}
            $<TARGET_FILE_DIR:${PROJECT_NAME}>
        )
    endif()
endif(WIN32)
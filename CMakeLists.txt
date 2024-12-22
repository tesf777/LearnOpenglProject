cmake_minimum_required(VERSION 3.10)
project(LearnOpenGL)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 添加编译选项
if(MSVC)
    add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
endif()

set(SOURCE_DIR ${CMAKE_SOURCE_DIR}/source/src)
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/source/include)
set(OPENGL_DIR ${CMAKE_SOURCE_DIR}/opengl)

# 添加全局 include 目录
include_directories(${INCLUDE_DIR})
include_directories(${OPENGL_DIR}/glad/include)
include_directories(${OPENGL_DIR}/glfw/include)
include_directories(${OPENGL_DIR}/glm)

# 构建 opengl/glad
add_library(glad ${OPENGL_DIR}/glad/glad.c)
target_include_directories(glad PUBLIC ${OPENGL_DIR}/glad/include)

# 构建 opengl/glfw
add_library(glfw STATIC IMPORTED)
set_target_properties(glfw PROPERTIES IMPORTED_LOCATION ${OPENGL_DIR}/glfw/lib/glfw3.lib)

# 添加子目录 (为每个示例项目提供独立的 CMakeLists.txt 文件)
add_subdirectory(${SOURCE_DIR}/1_Helloworld)
add_subdirectory(${SOURCE_DIR}/2_VBO)
add_subdirectory(${SOURCE_DIR}/3_Uniform)


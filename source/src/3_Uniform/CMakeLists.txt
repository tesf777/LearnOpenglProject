# 设置目标名称
set(TARGET_NAME 3_Uniform)

# 添加可执行文件
add_executable(${TARGET_NAME} uniform.cpp ${INCLUDE_DIR}/MyShader.cpp)

# 链接 glad 和 glfw
target_link_libraries(${TARGET_NAME} glad glfw opengl32)

# 设置 include 目录 (继承自父目录，但可以额外添加子模块路径)
target_include_directories(${TARGET_NAME} PRIVATE ${INCLUDE_DIR})



file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/shaders DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Debug)
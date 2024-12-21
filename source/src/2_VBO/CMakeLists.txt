set(TARGET_NAME VBO)

add_executable(${TARGET_NAME} VBO.cpp)

target_link_libraries(${TARGET_NAME} glad glfw opengl32)

target_include_directories(${TARGET_NAME} PRIVATE ${INCLUDE_DIR})
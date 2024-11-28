set(TARGET_NAME hellorectangle)

add_executable(${TARGET_NAME} helloworld.cpp)

target_link_libraries(${TARGET_NAME} glad glfw opengl32)

target_include_directories(${TARGET_NAME} PRIVATE ${INCLUDE_DIR})
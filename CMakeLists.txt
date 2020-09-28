
cmake_minimum_required(VERSION 3.15)
project(OpenGL)

set(CMAKE_CXX_STANDARD 14)
find_package(glfw3 3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)


include_directories(${OPENGL_INCLUDE_DIR})


################################################

add_executable(OpenGL main.cpp window.cpp window.h buffer.cpp buffer.h) #common to all clion project

target_link_libraries(OpenGL glfw)

target_link_libraries(OpenGL GLEW)


target_link_libraries(OpenGL OpenGL::GL)

#################################################
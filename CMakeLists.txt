
cmake_minimum_required(VERSION 3.15)
project(OpenGL)

set(CMAKE_CXX_STANDARD 14)

set(OpenGlLinkers -lglut -lGLU -lGL) # setting all the Glut libraries as one variable.


include_directories(${OPENGL_INCLUDE_DIR})


################################################

add_executable(OpenGL main.cpp ) #common to all clion project
target_link_libraries(OpenGL ${OpenGlLinkers}) # linking opengl libraries to the project

#################################################
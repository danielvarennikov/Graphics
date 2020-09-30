//
// Created by dani on 28/09/2020.
//
#include <GLFW/glfw3.h>
#ifndef OPENGL_WINDOW_H
#define OPENGL_WINDOW_H

GLFWwindow* create_window();

unsigned int create_buffer();

void render_buffer(int size,int starting_index,int attribute_num, float positions[]);

void switch_to_window(GLFWwindow* window);


#endif //OPENGL_WINDOW_H

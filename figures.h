//
// Created by dani on 30/09/2020.
//
#include <GLFW/glfw3.h>


#ifndef OPENGL_FIGURES_H
#define OPENGL_FIGURES_H

enum class shapeType{

    TRIANGLE = -1, SQUARE = 0

};

void drawFigure(shapeType type, GLFWwindow* window);

#endif //OPENGL_FIGURES_H

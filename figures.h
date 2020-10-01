//
// Created by dani on 30/09/2020.
//
#include <GLFW/glfw3.h>
#include <iostream>

#ifndef OPENGL_FIGURES_H
#define OPENGL_FIGURES_H

enum class shapeType{

    TRIANGLE = -1, SQUARE = 0

};

struct UniformColorSet{

    float first;
    float second;
    float third;
    float fourth;

};

void drawFigure(shapeType type, GLFWwindow* window, float change, int element, UniformColorSet set);

UniformColorSet uniformMode(unsigned int shader,const char* variable, float first, float second, float third, float fourth);

#endif //OPENGL_FIGURES_H

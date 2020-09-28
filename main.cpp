#include "window.h"
#include <iostream>



#include <GLFW/glfw3.h>



#include <stdlib.h>

#include <GL/gl.h>

int main(void){

    GLFWwindow* window = create_window();
    switch_to_window(window);


    return 0;



}
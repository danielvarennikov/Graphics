//
// Created by dani on 28/09/2020.
//

#include <iostream>
#include <GLFW/glfw3.h>


GLFWwindow* create_window(){

    GLFWwindow* window;

    if(!glfwInit())
        return NULL;


    //Create the window
    window = glfwCreateWindow(640, 480 , "Hello World", NULL ,NULL);
    if(!window){

        glfwTerminate();
        return NULL;

    }

    return window;

}


void switch_to_window(GLFWwindow* window){

    //Make current context
    glfwMakeContextCurrent(window);

    //Loop until the user closes the window
    while(!glfwWindowShouldClose(window)){


        //Render
        glClear(GL_COLOR_BUFFER_BIT);

        //Swap front and back buffer
        glfwSwapBuffers(window);

        //Process events
        glfwPollEvents();

    }

}




//
// Created by dani on 30/09/2020.
//

#include "figures.h"

void drawFigure(shapeType type,GLFWwindow* window){

    //Loop until the user closes the window
    while( !glfwWindowShouldClose( window ) )
    {
        //Render here
        glClear( GL_COLOR_BUFFER_BIT );

        glDrawArrays( GL_TRIANGLES, 0, (type == shapeType::TRIANGLE)? 6 : 12);

        //Swap front and back buffers
        glfwSwapBuffers( window );

        //Poll for and process events
        glfwPollEvents();
    }

}
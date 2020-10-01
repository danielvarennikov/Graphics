//
// Created by dani on 30/09/2020.
//

#include <GL/glew.h>
#include "figures.h"

int location;


UniformColorSet uniformMode(unsigned int shader,const char* variable, float first, float second, float third, float fourth){

    //If using uniforms( moving the colors from the shader file here ):
    //Get the location of the variable we want to change
    location = glGetUniformLocation(shader, variable);

    //Create the color and return it
    return {first,second,third,fourth};
}


void drawFigure(shapeType type,GLFWwindow* window, float change,int element,UniformColorSet set){

    float runner;
    //Save the animated variable
    //TODO: fix bloat
    if(change != 0){

        switch(element){
            case 0:
                runner =  set.first;
                break;
            case 1:
                runner =  set.second;
                break;
            case 2:
                runner =  set.third;
                break;
            case 3:
                runner =  set.fourth;
                break;

        }

    }

    //Loop until the user closes the window
    while( !glfwWindowShouldClose( window ) )
    {

        //Render here
        glClear( GL_COLOR_BUFFER_BIT );

        glDrawArrays( GL_TRIANGLES, 0, (type == shapeType::TRIANGLE)? 6 : 12);

        //Check if a color animation was inserted: change is not 0
        if(change != 0){

            std::cout<< "Animated colors" <<std::endl;

            runner +=change;

            //Values must be between 0 and 1
            if(runner > 1.0f || runner < 0.0f)
                change = -change;

            //Now check which element is to be changed
            //TODO: multiple element changes
            switch(element) {
                case 0:
                    glUniform4f(location, runner, set.second, set.third, set.fourth);
                    break;
                case 1:
                    glUniform4f(location, set.first, runner, set.third, set.fourth);
                    break;
                case 2:
                    glUniform4f(location, set.first, set.second, runner, set.fourth);
                    break;
                case 3:
                    glUniform4f(location, set.first, set.second, set.third, runner);
                    break;

            }
        }

        //Swap front and back buffers
        glfwSwapBuffers( window );

        //Poll for and process events
        glfwPollEvents();
    }

}
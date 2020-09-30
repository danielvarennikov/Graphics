#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "window.h"
#include "shader.h"
#include "figures.h"
using namespace std;

int main( int argc, char** argv ){

    GLFWwindow* window = create_window();

    //Parse the shaders
    ShaderProgramSource source = parseShader("./shaders");

    unsigned int shader = createShader( source.VertexSource, source.FragmentSource );
    glUseProgram( shader );
    
    float positions[ 12 ] = {
            -0.5f, -0.5f,
            0.5f, -0.5f,
            0.5f,  0.5f,

            0.5f,  0.5f,
            -0.5f,  0.5f,
            -0.5f, -0.5f
    };

    //Create a vertex buffer
    create_buffer();

    //Render it
    render_buffer(12,0,2,positions);

    drawFigure(shapeType::SQUARE,window);

    glfwTerminate();
    return 0;
}
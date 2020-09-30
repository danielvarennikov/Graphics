#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "window.h"
#include "shader.h"
#include "figures.h"
using namespace std;

int main( int argc, char** argv ){

    GLFWwindow* window = create_window();

    GLuint vao = 0;
    glCreateVertexArrays( 1, &vao );
    glBindVertexArray( vao );

    //Parse the shaders
    ShaderProgramSource source = parseShader("./shaders");

    unsigned int shader = createShader( source.VertexSource, source.FragmentSource );
    glUseProgram( shader );

    float positions[ 6 ] = {
            -0.5f, -0.5f,
            0.5f, -0.5f,
            0.0f,  0.5f,
    };

    //Create a vertex buffer
    create_buffer();

    //Render it
    render_buffer(6,0,2,positions);

    drawTriangle(window);

    glfwTerminate();
    return 0;
}
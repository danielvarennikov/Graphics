#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "window.h"
#include "shader.h"
using namespace std;

int main( int argc, char** argv ){

    GLFWwindow* window = create_window();

    //Make the window's context current
    glfwMakeContextCurrent( window );
    if( glewInit() != GLEW_OK )
        cout << "error" << endl;

    cout << glGetString( GL_VERSION ) << endl;

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
    unsigned int buffer;
    glGenBuffers( 1, &buffer );
    glBindBuffer( GL_ARRAY_BUFFER, buffer );
    glBufferData( GL_ARRAY_BUFFER, 6 * sizeof( float ), positions, GL_STATIC_DRAW );
    glEnableVertexAttribArray( 0 );
    glVertexAttribPointer( 0, 2, GL_FLOAT, GL_FALSE, sizeof( float ) * 2, 0 );

    //Loop until the user closes the window
    while( !glfwWindowShouldClose( window ) )
    {
        //Render here
        glClear( GL_COLOR_BUFFER_BIT );

        glDrawArrays( GL_TRIANGLES, 0, 3 );

        //Swap front and back buffers
        glfwSwapBuffers( window );

        //Poll for and process events
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
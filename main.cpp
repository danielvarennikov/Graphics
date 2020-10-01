#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <signal.h>
#include "window.h"
#include "shader.h"
#include "figures.h"

//Stop running if GL throws an error on the log call
#define ASSERT(TEST) if(!(TEST)) raise(SIGTRAP);

//Wrap functions to Clear errors and crash
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))

using namespace std;

static void GLClearError(){

    //Clean all the errors
    while(glGetError() != GL_NO_ERROR);

}

static bool GLLogCall(const char* function, const char* file, int line){

    //Print all the errors
    while (GLenum error = glGetError()){
        cout << "[GL Error] : " << error << " " << function << " " << file << " : " << line << endl;
        return false;
    }

    return true;
}

int main( int argc, char** argv ){

    GLFWwindow* window = create_window();

    //Parse the shaders
    ShaderProgramSource source = parseShader("./shaders");

    unsigned int shader = createShader( source.VertexSource, source.FragmentSource );
    glUseProgram( shader );


    UniformColorSet colors = uniformMode(shader, "u_Color",0.5,0.5,0.5,0.5);

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

    drawFigure(shapeType::SQUARE,window,0.01,0,colors);

    glfwTerminate();
    return 0;
}
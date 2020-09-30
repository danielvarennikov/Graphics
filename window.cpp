//
// Created by dani on 28/09/2020.
//

#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "window.h"

float positions[6] = {
        -0.5f, -0.5f,
        0.0f,  0.5f,
        0.5f, -0.5f
};


static unsigned int CompileShader(const std::string& source, unsigned int type){

    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);


    //Error checking
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if(result == GL_FALSE){

        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout<<"Failed to compile "<< (type == GL_VERTEX_SHADER? "Vertex!" : "Fragment!")<<std::endl;
        std::cout<<message<<std::endl;
        glDeleteShader(id);
        return 0;

    }


    return id;

}

static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader){

    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(vertexShader, GL_VERTEX_SHADER);
    unsigned int fs = CompileShader(fragmentShader, GL_FRAGMENT_SHADER);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;

}


unsigned int create_buffer(){

    //The address
    unsigned int buffer;


    //Assign 1 buffer to the address
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);

    return buffer;

}


void render_buffer(int size,int starting_index,int attribute_num, float positions[]){

    glBufferData(GL_ARRAY_BUFFER, size * sizeof(float), positions, GL_STATIC_DRAW);

    glEnableVertexAttribArray(starting_index);

    //Index, number of attributes, type of attributes, normalised, size of each vertex, texture coordinate offset
    glVertexAttribPointer(starting_index, attribute_num,GL_FLOAT, GL_FALSE, sizeof(float) * attribute_num, 0);


}


GLFWwindow* create_window(){

    GLFWwindow* window;

    if(!glfwInit())
        return NULL;

    //Nvidia compliance
    glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
    glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );

    //Create the window
    window = glfwCreateWindow(640, 480 , "Hello World", NULL ,NULL);
    if(!window){

        glfwTerminate();
        return NULL;

    }

    //Make the window's context current
    glfwMakeContextCurrent( window );
    if( glewInit() != GLEW_OK )
        std::cout << "error" << std::endl;

    std::cout << glGetString( GL_VERSION ) << std::endl;

    return window;

}


void switch_to_window(GLFWwindow* window){

    glewInit();

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




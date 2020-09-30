//
// Created by dani on 28/09/2020.
//

#include <iostream>
#include <GL/glew.h>
#include "window.h"

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

    GLuint vao = 0;
    glCreateVertexArrays( 1, &vao );
    glBindVertexArray( vao );

    return window;

}






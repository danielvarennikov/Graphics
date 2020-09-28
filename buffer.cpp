//
// Created by dani on 28/09/2020.
//

#include <GL/glew.h>
#include "buffer.h"


unsigned int create_buffer(){

    //The address
    unsigned int buffer;

    //Assign 1 buffer to the address
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);

    return buffer;

}

void render_buffer(int size, float positions[]){

    glBufferData(GL_ARRAY_BUFFER, size * sizeof(float), positions, GL_STATIC_DRAW);

}


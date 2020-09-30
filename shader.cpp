//
// Created by dani on 30/09/2020.
//

#include "shader.h"
#include "shader.h"
#include <GL/glew.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

unsigned int compileShader( unsigned int type, const string& source ){

    unsigned int id = glCreateShader( type );

    //Gl accepts shaders in C style strings
    const char* src = source.c_str();

    glShaderSource( id, 1, &src, nullptr );
    glCompileShader( id );


    //Check the compiled shader for errors
    int result = 0;
    glGetShaderiv( id, GL_COMPILE_STATUS, &result );
    if( result == GL_FALSE ){
        int length = 0;
        glGetShaderiv( id, GL_INFO_LOG_LENGTH, &length );
        char* message = (char*)alloca( length * sizeof( char ) );
        glGetShaderInfoLog( id, length, &length, message );
        cout << "Failed to compile " << ( type == GL_VERTEX_SHADER ? "vertex" : "fragment" ) << "shader" << endl;
        cout << message << endl;
        glDeleteShader( id );
    }

    return id;
}

int createShader( const string& vertexShader, const string& fragmentShader ){

    //Create a program without the shaders
    unsigned int program = glCreateProgram();

    //First compile the vertex shader, the fragments afterwards
    unsigned int vs = compileShader( GL_VERTEX_SHADER, vertexShader );
    unsigned int fs = compileShader( GL_FRAGMENT_SHADER, fragmentShader );

    //Attach the shaders to the program
    glAttachShader( program, vs );
    glAttachShader( program, fs );
    glLinkProgram( program );
    glValidateProgram( program );

    //After attachment delete them
    glDeleteShader( vs );
    glDeleteShader( fs );

    return program;

}

ShaderProgramSource parseShader(const std::string& filepath){

    enum class shaderType{

        NONE = -1, VERTEX = 0, FRAGMENT = 1

    };

    //Find the type of the shader from the file
    ifstream stream(filepath);
    string line;
    stringstream ss[2];
    shaderType type = shaderType::NONE;
    while(getline(stream, line)){

        //Shader is found on the line
        if(line.find("#shader") != string::npos){

            if(line.find("vertex") != string::npos) {
                //Set mode to vertex
                type = shaderType::VERTEX;
            }else{
                //Set mode to fragment
                type = shaderType::FRAGMENT;

            }

        }else{

            //Add the line to the stream
            ss[(int)type] << line <<'\n';

        }
    }

    //Return the struct of the Shaders
    return {ss[0].str(), ss[1].str()};

}
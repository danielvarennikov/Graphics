//
// Created by dani on 30/09/2020.
//

#include <string>
using namespace std;

#ifndef OPENGL_SHADER_H
#define OPENGL_SHADER_H

struct ShaderProgramSource{

    string VertexSource;
    string FragmentSource;

};


unsigned int compileShader( unsigned int type, const string& source );

int createShader( const string& vertexShader, const string& fragmentShader );

ShaderProgramSource parseShader(const std::string& filepath);


#endif //OPENGL_SHADER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

struct ShaderProgramSource{

    string VertexSource;
    string FragmentSource;

};

static unsigned int compileShader( unsigned int type, const string& source ){

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

static int createShader( const string& vertexShader, const string& fragmentShader ){

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

static ShaderProgramSource parseShader(const std::string& filepath){

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

int main( void ){

    GLFWwindow* window;

    //Initialize the library
    if( !glfwInit() )
        return -1;

    //Nvidia Graphics compliance
    glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
    glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );

    //Create a windowed mode window and its OpenGL context
    window = glfwCreateWindow( 640, 480, "Hello World", NULL, NULL );
    if( !window ){
        glfwTerminate();
        return -1;
    }

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
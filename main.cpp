#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
using namespace std;


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

    string vertexShader =
            "#version 330 core\n"
            "\n"
            "layout ( location = 0 ) in vec4 position;"
            "\n"
            "void main(){\n"
            "gl_Position = position;\n"
            "}\n";
    string fragmentShader =
            "#version 330 core\n"
            "\n"
            "layout ( location = 0 ) out vec4 color;"
            "\n"
            "void main(){\n"
            "color = vec4(0.7,0.5,0.2,0.5);\n"
            "}\n";

    unsigned int shader = createShader( vertexShader, fragmentShader );
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
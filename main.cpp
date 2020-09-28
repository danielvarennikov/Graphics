#include "window.h"
#include <GLFW/glfw3.h>

int main(void){

    float positions[6] = {
            -0.5f, -0.5f,
             0.0f,  0.5f,
             0.5f, -0.5f
    };

    GLFWwindow* window = create_window();
    switch_to_window(window);

    return 0;

}
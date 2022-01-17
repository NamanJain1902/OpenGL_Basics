#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create GLFWwindow(window datatype) object
    GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "NJ's  Window", NULL, NULL);

    // Error check if window fails to create
    if(window == NULL) {
        std::cout << "Failed to load window" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Introduce the window into the current context.
    glfwMakeContextCurrent(window);

    // Load glad so it configures OpenGL
    gladLoadGL();


    // Sets the viewport of OpenGL in the window.
    // In this case the viewport goes from x=0, y=0, to x=800, y=800
    glViewport(0, 0, 800, 800);

    // Specify the color of the background.
    glClearColor(0.07f, 0.13f, 0.17f, 1.0f); // last value is alpha value that sets transparency level.
    // Clean the back buffer and assign the new color to it.
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(window);

    while(!glfwWindowShouldClose(window)) 
    {
        glfwPollEvents(); 
        // like window appearing, reszing etc, if we don't procees those 
        // events, the window will be in a state of not responding.


    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
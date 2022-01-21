#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;

const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";
const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";

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

    // Specify the color of the background. // The Back buffer with the color we want.
    glClearColor(0.07f, 0.13f, 0.17f, 1.0f); // last value is alpha value that sets transparency level.
    // Clean the back buffer and assign the new color to it.
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(window);



    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ----------------------- values in range [-1, 1] -------------------------
    GLfloat vertices[] = {
        -0.5f, -0.5f, 0.0f, // left
         0.5f, -0.5f, 0.0f, // right
         0.0f,  0.5f, 0.0f  // top
    };

    /**
     * @brief Shaders(objects) are in memory and we can only access them by references aka values.
     * all opengl objects accessed by references
     */
    //  Vertex Shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // Fragment Shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);


    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    //////////
    // check for linking errors
    // glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    // if (!success) {
    //     glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    //     std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    // }
    /////////

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);


    GLuint VAO, VBO; // VBO is array of references, since we have only one object we only need one.
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    // binding in opengl means we make certain object the current object.
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // Static means vertices will be modified once in many-2 time and
    // dynamic means vertices will be modified many many times.
    // DRAW means the vertices will be modified and we use to draw imange on the screen
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); 


    // (PositionOfVertexAttribute, HowManyValuesPerVertex, , AmountOfDataInEachVertex)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    

    while(!glfwWindowShouldClose(window)) 
    {
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f); 

        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3); // speicifying the type of primitive we use.
        glfwSwapBuffers(window);

        // Take care of GLFW events.
        glfwPollEvents(); 
        // like window appearing, reszing etc, if we don't procees those 
        // events, the window will be in a state of not responding.



    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
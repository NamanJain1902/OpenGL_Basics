#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<cmath>

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




    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ----------------------- values in range [-1, 1] -------------------------
    GLfloat vertices[] =
	{
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower left corner
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower right corner
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f, // Upper corner
		-0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner left
		0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner right
		0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f // Inner down
	};


    GLfloat indices[] = {
        0, 3, 5, // Lower left triangle
		3, 2, 4, // Lower right triangle
		5, 4, 1 // Upper triangle
    };


    GLuint VAO, VBO, EBO; // VBO is array of references, since we have only one object we only need one.
    // Generate the VAO, VBO, and EBO with only 1 object each
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    // binding in opengl means we make certain object the current object.
    // Make the VAO the current Vertex Array Object by binding it
    glBindVertexArray(VAO);
    // Bind the VBO specifying it's a GL_ARRAY_BUFFER
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // Bind the EBO specifying it's a GL_ELEMENT_ARRAY_BUFFER
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    // Static means vertices will be modified once in many-2 time and
    // dynamic means vertices will be modified many many times.
    // DRAW means the vertices will be modified and we use to draw imange on the screen
    // Introduce the vertices into the VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); 
    // Introduce the indices into the EBO
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // (PositionOfVertexAttribute, HowManyValuesPerVertex, , AmountOfDataInEachVertex)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);


	// Bind both the VBO and VAO to 0 so that we don't accidentally modify the VAO and VBO we created
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    // Bind the EBO to 0 so that we don't accidentally modify it
	// MAKE SURE TO UNBIND IT AFTER UNBINDING THE VAO, as the EBO is linked in the VAO
	// This does not apply to the VBO because the VBO is already linked to the VAO during glVertexAttribPointer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    

    while(!glfwWindowShouldClose(window)) 
    {
        // Specify the color of the background
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f); 

        // clean the back buffer and assign the new colot to it.
        glClear(GL_COLOR_BUFFER_BIT);

        // tell OpenGL which Shader Program we want to use.
        glUseProgram(shaderProgram);
        
        // Bind the VAO so OpenGL knows to use it.
        glBindVertexArray(VAO);

        // Draw the triangle using the GL_TRIANGLES primitive.
        // glDrawArrays(GL_TRIANGLES, 0, 3); // speicifying the type of primitive we use.
        // Draw primitives, number of indices, datatype of indices, index of indices
        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, (void*)0);

        // Swap the back buffer with the front buffer.
        glfwSwapBuffers(window);

        // Take care of GLFW events.
        glfwPollEvents(); 
        // like window appearing, reszing etc, if we don't procees those 
        // events, the window will be in a state of not responding.

    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
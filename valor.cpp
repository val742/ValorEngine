// Valor engine by Valores M.
// Using GLFW to create window and process input
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

// Header
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// Settings
const unsigned int SCR_WIDTH = 1280;
const unsigned int SCR_HEIGHT = 720;

const char* vertexShaderSource = "#version 430 core\n"
"layout (location = 0) in vec3 aPos;\n" // Referenced in glVertexAttribPointer
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
const char* fragmentShaderSource = "#version 430 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"};\n\0";


int main(void)
{
    // Init and config for glfw
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // Window creation
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Valor Engine", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window." << std::endl;
        glfwTerminate();
        return -1;
    };
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Load glad pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    };

    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT); 


    // Vertex Shader / Node Shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    // Testing Vertex Shader / Node
    int  success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    };
    
    // Fragment Shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    // Testing Fragment Shader
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    };

    // Shader Program Setup / Linking Shaders
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Shader Program Testing
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
    };

    // Activate new Program and CleanUp
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);


    // Linking Vertex Attributes / Node
    // Setup vertex data
    //float vertices[] = {
    //    //first triangle
    //    -0.5f, -0.5f, 0.0f, // top right
    //     0.5f, -0.5f, 0.0f, // bottom right
    //     0.0f,  0.5f, 0.0f, // top left
    //     // 2nd triangle
    //     0.5f, -0.5f, 0.0f, // bottom right
    //    -0.5f, -0.5f, 0.0f, // bottom left
    //    -0.5f, -0.5f, 0.0f // top left
    // };

    float vertices[] = {
        0.5f,  0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f,

    };

    unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3
    };

    unsigned int indicesStar[] = {
        0,4,5,
        1,4,7,
        2,7,6,
        3,6,5,
        5,4,7,
        5,6,7
    };

    float verticesStar[] = {
        0.0f, 0.6f, 0.0f, //0
        0.6f, 0.0f, 0.0f, //1
        0.0f, -0.6f, 0.0f, //2
        -0.6f, 0.0f, 0.0f, //3
        0.25f, 0.25f, 0.0f, //4
        -0.25f, 0.25f, 0.0f, //5
        -0.25f, -0.25f, 0.0f, //6
        0.25f, -0.25f, 0.0f //7
    };

    // VBO - VAO - EBO
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesStar), verticesStar, GL_STATIC_DRAW);

    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicesStar), indicesStar, GL_STATIC_DRAW);


    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);// Referenced in glVertexAttribPointer; data stored in floating point values
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    
    glBindVertexArray(0);

    
    // Render loop
    while (!glfwWindowShouldClose(window)) {
        // input
        processInput(window);

        // render 
        // --------------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);


        // drawingTriangle
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        // glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glDrawElements(GL_TRIANGLES, 3 * 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        // check and call events and swap the buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    };
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);
    glfwTerminate();
    return 0;

};


// glfw: updates size when window is updated 
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
};

// process all input
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
};
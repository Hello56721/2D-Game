#include <iostream>

#include <EngineGraphics/Utils.hpp>
#include <GLFW/glfw3.h>

int main() {
    if (!glfwInit()) {
        std::cout << "ERROR: Could not initialize GLFW." << std::endl;
        return -1;
    }
    // Make GLFW use OpenGL 3.3 core or higher
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    // Hide the GLFW window on startup
    glfwWindowHint(GLFW_VISIBLE, false);

    GLFWwindow* window = glfwCreateWindow(800, 600, "2D Game", nullptr, nullptr);
    if (window == nullptr) {
        std::cout << "ERROR: Failed to create GLFW window." << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    
    // Put the window in the center of the screen
    const GLFWvidmode* videoMode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    glfwSetWindowPos(window, (videoMode->width - 800) / 2, (videoMode->height - 600) / 2);

    // Load the OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "ERROR: Failed to load OpenGL function pointers" << std::endl;
        glfwTerminate();
        return -1;
    }

    float vertices[] = {
         0.5f,  0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f
    };
    unsigned int indices[] = {
        0, 1, 2,
        0, 3, 2
    };
    
    unsigned int vertexArray;
    glCall(glGenVertexArrays(1, &vertexArray));
    glCall(glBindVertexArray(vertexArray));
    
    unsigned int vertexBuffer;
    glCall(glGenBuffers(1, &vertexBuffer));
    glCall(glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer));
    glCall(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));
    
    unsigned int elemenBuffer;
    glCall(glGenBuffers(1, &elemenBuffer));
    glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elemenBuffer));
    glCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW));
    
    glCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0));
    glCall(glEnableVertexAttribArray(0));
    
    glfwShowWindow(window);
    while (!glfwWindowShouldClose(window)) {
        glCall(glClearColor(1.0f, 0.5f, 0.0f, 1.0f));
        glCall(glClear(GL_COLOR_BUFFER_BIT));

        glCall(glBindVertexArray(vertexArray));
        glCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

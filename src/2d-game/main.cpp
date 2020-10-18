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
    
    glCall(glBindBuffer(GL_UNSIGNED_INT, 0));
    
    glfwShowWindow(window);
    while (!glfwWindowShouldClose(window)) {
        glCall(glClearColor(1.0f, 0.5f, 0.0f, 1.0f));
        glCall(glClear(GL_COLOR_BUFFER_BIT));

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

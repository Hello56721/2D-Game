#include "Display.hpp"

GLFWwindow* Display::window;

unsigned int Display::width;
unsigned int Display::height;

void Display::create(bool fullscreen) {
    if (!glfwInit()) {
        std::cout << "ERROR: Could not initialize GLFW." << std::endl;
        return;
    }
    // Make GLFW use OpenGL 3.3 core or higher
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    // Hide the GLFW window on startup
    glfwWindowHint(GLFW_VISIBLE, false);
    
    // information about the monitor
    const GLFWvidmode* videoMode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    
    if (fullscreen) {
        width = videoMode->width;
        height = videoMode->height;
        window = glfwCreateWindow(width, height, "2D Game", glfwGetPrimaryMonitor(), nullptr);
    } else {
        width = videoMode->width / 2;
        height = videoMode->height / 2;
        window = glfwCreateWindow(width, height, "2D Game", nullptr, nullptr);
    }
    
    // Check if the window is legit
    if (window == nullptr) {
        std::cout << "ERROR: Failed to create GLFW window." << std::endl;
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(window);
    
    // Put the window in the center of the screen
    glfwSetWindowPos(window, (videoMode->width - 800) / 2, (videoMode->height - 600) / 2);

    // Load the OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "ERROR: Failed to load OpenGL function pointers" << std::endl;
        glfwTerminate();
        return;
    }
}

bool Display::isOpen() {
    return (!glfwWindowShouldClose(window));
}

void Display::update() {
    glfwSwapBuffers(window);
    glfwPollEvents();
}

void Display::framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    Display::width = width;
    Display::height = height;
    glCall(glViewport(0, 0, width, height));
}
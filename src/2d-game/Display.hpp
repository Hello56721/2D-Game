#ifndef INCLUDED_2d_game_Display_hpp
#define INCLUDED_2d_game_Display_hpp

#include <GLFW/glfw3.h>

namespace Display {
    // the window handle
    extern GLFWwindow* window;
    
    // width and height of the window
    unsigned int width;
    unsigned int height;
    
    // Initialize and create the window
    void create(bool fullscreen);
    
    // returns if the window is open or not
    bool isOpen();
    
    // Update the window
    void update();
    
    // The framebuffer size callback
    void framebufferSizeCallback(GLFWwindow* window, int width, int height);
}

#endif
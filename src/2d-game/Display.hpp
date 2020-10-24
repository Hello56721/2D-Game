#ifndef INCLUDED_2d_game_Display_hpp
#define INCLUDED_2d_game_Display_hpp

#include <EngineGraphics/Utils.hpp>
#include <GLFW/glfw3.h>

#include <iostream>

namespace Display {
    // the window handle
    extern GLFWwindow* window;
    
    // width and height of the window
    extern unsigned int width;
    extern unsigned int height;
    
    // Initialize and create the window
    void create(bool fullscreen);
    
    // returns if the window is open or not
    bool isOpen();
    
    // Update the window
    void update();
    
    // The framebuffer size callback
    void framebufferSizeCallback(GLFWwindow* window, int width, int height);
    
    // Returns if the specified key is pressed down
    bool isKeyDown(int key);
}

#endif
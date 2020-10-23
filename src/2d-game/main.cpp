#include <iostream>

#include <EngineGraphics/Utils.hpp>
#include "Display.hpp"

#include <EngineGraphics/Shader.hpp>
#include <EngineGraphics/Mesh.hpp>

int main() {
    Display::create(false);
    
    std::vector<Vertex> vertices = {
        {{ 0.5f,  0.5f, 0.0f}},
        {{ 0.5f, -0.5f, 0.0f}},
        {{-0.5f, -0.5f, 0.0f}},
        {{-0.5f,  0.5f, 0.0f}}
    };
    std::vector<unsigned int> indices = {
        0, 1, 2,
        0, 3, 2
    };
    
    EngineGraphics::Mesh* mesh = new EngineGraphics::Mesh(vertices, indices);
    
    EngineGraphics::Shader* shader = new EngineGraphics::Shader("../shaders/basic/vertex.glsl", "../shaders/basic/fragment.glsl", "shader program");
    
    glfwShowWindow(Display::window);
    while (Display::isOpen()) {
        glCall(glClearColor(1.0f, 0.5f, 0.0f, 1.0f));
        glCall(glClear(GL_COLOR_BUFFER_BIT));
        
        shader->use();
        mesh->render();

        //glfwSwapBuffers(window);
        //glfwPollEvents();
        Display::update();
    }
    
    delete mesh;
    delete shader;

    glfwTerminate();
    return 0;
}

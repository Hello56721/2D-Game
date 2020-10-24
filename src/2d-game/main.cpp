#include <iostream>

#include <EngineGraphics/Utils.hpp>
#include "Display.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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
    
    glm::mat4 coordinateSystems = glm::mat4(1.0f);
    
    glm::mat4 model = glm::mat4(1.0f);
    
    glm::mat4 view = glm::mat4(1.0f);
    view = glm::translate(view, glm::vec3(0.0, 0.0, -3.0));
    
    glm::mat4 projection;
    projection = glm::perspective(glm::radians(45.0f), static_cast<float>(Display::width) / static_cast<float>(Display::height), 0.1f, 100.0f);
    
    coordinateSystems = projection * view * model;
    
    glfwShowWindow(Display::window);
    while (Display::isOpen()) {
        glCall(glClearColor(1.0f, 0.5f, 0.0f, 1.0f));
        glCall(glClear(GL_COLOR_BUFFER_BIT));
        
        shader->use();
        
        shader->setUniform("coordinateSystems", coordinateSystems);
        
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

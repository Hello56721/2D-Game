#include <iostream>

#include <EngineGraphics/Utils.hpp>
#include "Display.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <EngineGraphics/Shader.hpp>
#include <EngineGraphics/Mesh.hpp>

void processInputs();

glm::mat4 model;
glm::mat4 view;
glm::mat4 projection;

double deltaTime;

int main(int argl, char* argv[]) {
    // Parse the command line options
    std::string args[argl];
    for (int i = 0; i < argl; i++) {
        args[i] = argv[i];
    }
    
    if (argl != 1) {
        if (args[1] == "--debug") {
            Display::create(false);
        } else {
            Display::create(true);
        }
    } else {
        Display::create(true);
    }
    
    std::vector<Vertex> vertices = {
        {{ 0.1f,  0.1f, 0.0f}},
        {{ 0.1f, -0.1f, 0.0f}},
        {{-0.1f, -0.1f, 0.0f}},
        {{-0.1f,  0.1f, 0.0f}}
    };
    std::vector<unsigned int> indices = {
        0, 1, 2,
        0, 3, 2
    };
    
    std::string vertexShaderPath = "../shaders/basic/vertex.glsl";
    std::string fragmentShaderPath = "../shaders/basic/fragment.glsl";
    
    EngineGraphics::Mesh* mesh = new EngineGraphics::Mesh(vertices, indices);
    
    EngineGraphics::Shader* shader = new EngineGraphics::Shader(vertexShaderPath, fragmentShaderPath, "shader program");
    
    glm::mat4 coordinateSystems = glm::mat4(1.0f);
    
    model = glm::mat4(1.0f);
    
    view = glm::mat4(1.0f);
    view = glm::translate(view, glm::vec3(0.0, 0.0, -3.0));
    
    projection = glm::perspective(glm::radians(45.0f), static_cast<float>(Display::width) / static_cast<float>(Display::height), 0.1f, 100.0f);
    
    double startTime, endTime;
    
    glfwShowWindow(Display::window);
    while (Display::isOpen()) {
        startTime = glfwGetTime();
        
        processInputs();
        
        coordinateSystems = projection * view * model;
        
        glCall(glClearColor(1.0f, 0.5f, 0.0f, 1.0f));
        glCall(glClear(GL_COLOR_BUFFER_BIT));
        
        shader->use();
        
        shader->setUniform("coordinateSystems", coordinateSystems);
        
        mesh->render();

        //glfwSwapBuffers(window);
        //glfwPollEvents();
        Display::update();
        
        endTime = glfwGetTime();
        deltaTime = endTime - startTime;
    }
    
    delete mesh;
    delete shader;

    glfwTerminate();
    return 0;
}

void processInputs() {
    if (Display::isKeyDown(GLFW_KEY_ESCAPE)) {
        glfwSetWindowShouldClose(Display::window, true);
    }
    
    if (Display::isKeyDown(GLFW_KEY_UP)) {
        model = glm::translate(model, glm::vec3(0.0, 0.5 * deltaTime, 0.0));
    }
    if (Display::isKeyDown(GLFW_KEY_DOWN)) {
        model = glm::translate(model, glm::vec3(0.0, -0.5 * deltaTime, 0.0));
    }
    if (Display::isKeyDown(GLFW_KEY_RIGHT)) {
        model = glm::translate(model, glm::vec3(0.5 * deltaTime, 0.0, 0.0));
    }
    if (Display::isKeyDown(GLFW_KEY_LEFT)) {
        model = glm::translate(model, glm::vec3(-0.5 * deltaTime, 0.0, 0.0));
    }
}
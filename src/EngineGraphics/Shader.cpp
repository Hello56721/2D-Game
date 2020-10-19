#include <algorithm>

#include <EngineGraphics/Shader.hpp>

using namespace EngineGraphics;

Shader::Shader(std::string_view vertexPath, std::string_view fragmentPath, std::string_view name) {
    unsigned int vertex = createShader(vertexPath, GL_VERTEX_SHADER);
    unsigned int fragment = createShader(fragmentPath, GL_FRAGMENT_SHADER);
    
    id = glCall(glCreateProgram());
    glCall(glAttachShader(id, vertex));
    glCall(glAttachShader(id, fragment));
    glCall(glLinkProgram(id));
    
    // Check for linking errors
    int sucess;
    glCall(glGetProgramiv(id, GL_LINK_STATUS, &sucess));
    if (sucess == GL_FALSE) {
        int infoLogLength;
        glCall(glGetProgramiv(id, GL_INFO_LOG_LENGTH, &infoLogLength));
        char* infoLog = new char[infoLogLength];
        glCall(glGetProgramInfoLog(id, infoLogLength, &infoLogLength, infoLog));
        
        std::cout << "WARNING: When linking " << name << ":\n";
        std::cout << infoLog << "\n\n";
    }
    
    // Don't the shaders anymore since they are linked to the program
    glCall(glDeleteShader(vertex));
    glCall(glDeleteShader(fragment));
}

Shader::Shader(Shader&& src) {
    glCall(glUseProgram(0));
    glCall(glDeleteProgram(id));
    
    id = src.id;
    src.id = 0;
}

Shader& Shader::operator=(Shader&& rhs) {
    glCall(glUseProgram(0));
    glCall(glDeleteProgram(id));
    
    id = rhs.id;
    rhs.id = 0;
    
    return *this;
}

void Shader::use() const {
    glCall(glUseProgram(id));
}

void Shader::setUniform(std::string_view p_name, bool value) const {
    std::string name = p_name.data();
    int location = glCall(glGetUniformLocation(id, name.c_str()));
    glCall(glUniform1i(location, static_cast<int>(value)));
}

void Shader::setUniform(std::string_view p_name, int value) const {
    std::string name = p_name.data();
    int location = glCall(glGetUniformLocation(id, name.c_str()));
    glCall(glUniform1i(location, value));
}

void Shader::setUniform(std::string_view p_name, float value) const {
    std::string name = p_name.data();
    int location = glCall(glGetUniformLocation(id, name.c_str()));
    glCall(glUniform1f(location, value));
}

Shader::~Shader() {
    glCall(glUseProgram(0));
    glCall(glDeleteProgram(id));
}
#include <EngineUtils/FileUtils.hpp>

#include <EngineGraphics/Utils.hpp>

void EngineGraphics::printErrors(std::string_view file, std::string_view line, int lineNum) {
    unsigned int errorCode = 0;
    while ((errorCode = glGetError()) != GL_NO_ERROR) {
        std::string error;
        switch (errorCode) {
        case GL_INVALID_ENUM:
            error = "GL_INVALID_ENUM";
            break;
        case GL_INVALID_VALUE:
            error = "GL_INVALID_VALUE";
            break;
        case GL_INVALID_OPERATION:
            error = "GL_INVALID_OPERATION";
            break;
        case GL_INVALID_FRAMEBUFFER_OPERATION:
            error = "GL_INVALID_FRAMEBUFFER_OPERATION";
            break;
        case GL_OUT_OF_MEMORY:
            error = "GL_OUT_OF_MEMORY";
            break;
        case GL_STACK_UNDERFLOW:
            error = "GL_STACK_UNDERFLOW";
            break;
        case GL_STACK_OVERFLOW:
            error = "GL_STACK_OVERFLOW";
            break;
        }

        std::cout << "ERROR: " << error << " at " << file << "[" << lineNum << "]";
        std::cout << " " << line << std::endl;
    }
}

unsigned int EngineGraphics::createShader(std::string_view sourcePath, unsigned int type) {
    // Load the shader source
    std::string source_str = EngineUtils::loadAsString(sourcePath);
    const char* source = source_str.c_str();
    
    unsigned int shader = glCall(glCreateShader(type));
    glCall(glShaderSource(shader, 1, &source, nullptr));
    glCall(glCompileShader(shader));
    
    // Check for compiliation errors
    int success;
    glCall(glGetShaderiv(shader, GL_COMPILE_STATUS, &success));
    if (success == GL_FALSE) { // success equal to GL_FALSE if there are compiliation errors
        int infoLogLength;
        glCall(glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength));
        char* infoLog = new char[infoLogLength];
        glCall(glGetShaderInfoLog(shader, infoLogLength, &infoLogLength, infoLog));
        
        std::cout << "WARNING: Compiling " << sourcePath << "resulted in:\n";
        std::cout << infoLog << "\n\n";
        
        delete[] infoLog;
    }
    
    return shader;
}
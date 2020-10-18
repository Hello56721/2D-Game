#ifndef INCLUDED_EngineGraphics_Shader_hpp
#define INCLUDED_EngineGraphics_Shader_hpp

#include <EngineGraphics/Utils.hpp>
#include <EngineUtils/FileUtils.hpp>

namespace EngineGraphics {
    class Shader {
    private:
        // the handle for the shader program
        unsigned int id;
    
    public:
        // Default constructor
        Shader() = default;
        
        // Create a shader program with the paths to the source
        Shader(std::string_view vertexPath, std::string_view fragmentPath, std::string_view name);
        
        // Prevent Copying and passing by value
        Shader(Shader& src) = delete;
        Shader& operator=(Shader& rhs) = delete;
        
        // Allow moving, though
        Shader(Shader&& src);
        Shader& operator=(Shader&& rhs);
        
        // use/run the shader program
        void use() const;
        
        // utility function for setting uniforms
        void setUniform(std::string_view name, bool value) const;
        void setUniform(std::string_view name, int value) const;
        void setUniform(std::string_view name, float value) const;
        
        // Destroys the shader program (obviously)
        virtual ~Shader();
    };
}

#endif
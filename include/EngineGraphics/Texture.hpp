#ifndef INCLUDED_EngineGraphics_Texture_hpp
#define INCLUDED_EngineGraphics_Texture_hpp

#include <string>
#include <string_view>

namespace EngineGraphics {
    class Texture {
    private:
        // the handle for the texture
        unsigned int texture;
    public:
        // Default constructor
        Texture() = default;
        
        // Constructor
        Texture(std::string_view pathToImageFile);
        
        // Copy constructor
        Texture(Texture& src);
        // Copy assignment operator
        Texture& operator=(Texture rhs);
        
        // Move constructor
        Texture(Texture&& src);
        // Move assignment operator
        Texture& operator=(Texture&& rhs);
        
        // Returns the Handle of the texture
        unsigned int getHandle();
        
        // Bind the texture
        void bind();
        
        // Set the active texture by texture unit
        static void setActive(unsigned int unit);
    };
}

#endif
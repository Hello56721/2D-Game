#ifndef INCLUDED_EngineGraphics_Mesh_hpp
#define INCLUDED_EngineGraphics_Mesh_hpp

#pragma once

#include <vector>
#include <EngineGraphics/Vertex.hpp>
#include <EngineGraphics/Utils.hpp>

namespace EngineGraphics {
    class Mesh {
    private:
        // the handles to OpenGL objects
        unsigned int vertexArray;
        unsigned int vertexBuffer;
        unsigned int elementBuffer;
        
        // vertices
        std::vector<Vertex> vertices;
        
        // indices
        std::vector<unsigned int> indices;
        
        // Build the mesh
        void build();
        
        // Move ownership from another object
        void moveFrom(Mesh& src);
        
        // Clean up all of the previous data
        void cleanup();
        
    public:
        // swap two meshes
        static void swap(Mesh& one, Mesh& two) noexcept;
        
        // Default constructor
        Mesh() = default;
        
        // Constructor
        Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);
        
        // Copy constructor and = operator
        Mesh(Mesh& src);
        Mesh& operator=(Mesh& rhs);
        
        // Move constructor and = operator
        Mesh(Mesh&& src);
        Mesh& operator=(Mesh&& rhs);
        
        // Render the mesh
        void render() const;
        
        // Destroy the mesh
        virtual ~Mesh();
    };
}

#endif
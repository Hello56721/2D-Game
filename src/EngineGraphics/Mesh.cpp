#include <algorithm>

#include <EngineGraphics/Mesh.hpp>

using namespace EngineGraphics;

void Mesh::build() {
    glCall(glGenVertexArrays(1, &vertexArray));
    glCall(glBindVertexArray(vertexArray));
    
    glCall(glGenBuffers(1, &vertexBuffer));
    glCall(glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer));
    glCall(glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW));
    
    glCall(glGenBuffers(1, &elementBuffer));
    glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer));
    glCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW));
    
    glCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0));
}

void Mesh::moveFrom(Mesh& src) {
    vertices = std::move(src.vertices);
    indices = std::move(src.indices);
    
    vertexArray = src.vertexArray;
    vertexBuffer = src.vertexBuffer;
    elementBuffer = src.elementBuffer;
    
    src.vertexArray = 0;
    src.vertexBuffer = 0;
    src.elementBuffer = 0;
    
    src.vertices = {};
    src.indices = {};
}

void Mesh::cleanup() {
    glCall(glBindVertexArray(0));
    glCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
    glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
    
    glCall(glDeleteVertexArrays(1, &vertexArray));
    glCall(glDeleteBuffers(1, &vertexBuffer));
    glCall(glDeleteBuffers(1, &elementBuffer));
    
    vertexArray = 0;
    vertexBuffer = 0;
    elementBuffer = 0;
    
    vertices = {};
    indices = {};
}

void Mesh::swap(Mesh& one, Mesh& two) noexcept {
    std::swap(one.vertexArray, two.vertexArray);
    std::swap(one.vertexBuffer, two.vertexBuffer);
    std::swap(one.elementBuffer, two.elementBuffer);
    
    std::swap(one.vertices, two.vertices);
    std::swap(one.indices, two.indices);
}

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices) {
    this->vertices = vertices;
    this->indices = indices;
    
    build();
}

Mesh::Mesh(Mesh& src) {
    vertices = src.vertices;
    indices = src.indices;
    
    build();
}

Mesh& Mesh::operator=(Mesh& rhs) {
    Mesh temp(rhs);
    swap(*this, temp);
    return *this;
}

Mesh::Mesh(Mesh&& src) {
    moveFrom(src);
}

Mesh& Mesh::operator=(Mesh&& rhs) {
    cleanup();
    
    moveFrom(rhs);
    
    return *this;
}

void Mesh::render() const {
    glCall(glBindVertexArray(vertexArray));
    glCall(glEnableVertexAttribArray(0));
    glCall(glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr));
    glCall(glDisableVertexAttribArray(0));
    glCall(glBindVertexArray(0));
}

Mesh::~Mesh() {
    cleanup();
}
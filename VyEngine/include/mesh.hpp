#pragma once

#include <texture.hpp>
#include <glm/glm.hpp>
#include <vector>


/*
    Structure for storing values for each vertex.
*/

struct Vertex
{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoord;

    // Generate a list of vertices.
    static std::vector<Vertex> genList(float* vertices, int numVertices);
};

/*
*   Mesh Class
* 
*   Contains:
*       - A vector list of vertices (Vertex) that each contain a position, normal, and UV coordinate vectors.
*       - A vector list of indices (unsigned int) for indexed drawing.
*       - A vector list of textures (Texture) that each contain data such as ID, type, name, and a directory path.
*       - 2 aiColor4D (RGBA) values for a materials diffuse & specular values.
*/

class Mesh
{
private:

    // True if mesh only has materials
    bool noTex;

    // Setup data with buffers
    void setup();
    
    unsigned int VBO, EBO;


public:

    // Vertex List
    std::vector<Vertex> vertices;

    // Index List
    std::vector<unsigned int> indices;
    
    // Texture List
    std::vector<MeshTexture> textures;

    // Material Diffuse value
    aiColor4D diffuse;

    // Material Specular value
    aiColor4D specular;

    // Vertex Array Object
    unsigned int VAO;

    // Constructors
    Mesh();

    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<MeshTexture> textures);

    // Destructor
    ~Mesh();

    void setupMesh();

    // Render a number of instances using a shader
    // void render(ShaderProgram &shader); //, unsigned int numInstances);

    void cleanup();
};
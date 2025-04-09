#include <mesh.hpp>

#pragma region VERTEX

std::vector<Vertex> Vertex::genList(float* vertices, int numVertices)
{
	std::vector<Vertex> vertList(numVertices);

	int stride = 8;

    for (int i = 0; i < numVertices; i++) 
    {
        vertList[i].position = glm::vec3(
            vertices[i * stride + 0],
            vertices[i * stride + 1],
            vertices[i * stride + 2]
        );

        vertList[i].normal = glm::vec3(
            vertices[i * stride + 3],
            vertices[i * stride + 4],
            vertices[i * stride + 5]
        );

        vertList[i].texCoord = glm::vec2(
            vertices[i * stride + 6],
            vertices[i * stride + 7]
        );
    }

    return vertList;
}

#pragma endregion


// Constructors
Mesh::Mesh() : noTex(false) {}


Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<MeshTexture> textures)
{
    this->vertices = vertices;
    this->indices  = indices;
    this->textures = textures;

    setupMesh();
}


// Destructor
Mesh::~Mesh()
{
    cleanup();
}


void Mesh::setupMesh()
{
    glGenVertexArrays(1, &VAO);

    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    // load data into vertex buffers
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // A great thing about structs is that their memory layout is sequential for all its items.
    // The effect is that we can simply pass a pointer to the struct and it translates perfectly to a glm::vec3/2 array which
    // again translates to 3/2 floats which translates to a byte array.
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);


    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    
    // vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

    // vertex texture coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));

    glBindVertexArray(0);
}


void Mesh::render(ShaderProgram &shader) //, unsigned int numInstances)
{
    // Setup Textures
    unsigned int diffIndex = 1;
    unsigned int specIndex = 1;
    unsigned int normIndex = 1;
    unsigned int hghtIndex = 1;

    for (unsigned int i = 0; i < textures.size(); i++)
    {
        // Activate Texture
        glActiveTexture(GL_TEXTURE0 + i);

        // retrieve texture info
        // retrieve texture number (the N in diffuseN)
        std::string name;
        switch (textures[i].type) 
        {
        case aiTextureType_DIFFUSE:
            name = "texture_diffuse" + std::to_string(diffIndex++);
            break;

        case aiTextureType_SPECULAR:
            name = "texture_specular" + std::to_string(specIndex++);
            break;

        case aiTextureType_HEIGHT:
            name = "texture_height" + std::to_string(hghtIndex++);
            break;

        case aiTextureType_NORMALS:
            name = "texture_normal" + std::to_string(normIndex++);
            break;

        default:
            name = textures[i].name;
            break;
        }

        // Set shader value
        shader.setUniform(name, i);

        // Bind Texture
        glBindTexture(GL_TEXTURE_2D, textures[i].ID);
    }

    // Draw Mesh
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(indices.size()), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    // Set back to default.
    glActiveTexture(GL_TEXTURE0);
}

void Mesh::cleanup()
{
    glBindVertexArray(0);

    //for (Texture t : textures) 
    //{
    //    t.cleanup();
    //}
}
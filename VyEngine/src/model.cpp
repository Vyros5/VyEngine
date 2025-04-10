#include "model.hpp"

// Had to be included here in the .cpp file.
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

Model::Model(const std::string &pPath)
{
    loadModel(pPath);
}


Model::~Model()
{
	cleanup();
}


void Model::render(ShaderProgram &shader)
{
    for (unsigned int i = 0; i < meshes.size(); i++)
    {
        meshes[i].render(shader);
    }
}


// Add a mesh to the list
void Model::addMesh(Mesh* mesh)
{
	meshes.push_back(*mesh);
}


void Model::cleanup()
{
	// cleanup each mesh
	for (size_t i = 0, len = meshes.size(); i < len; i++)
    {
		meshes[i].cleanup();
	}
}


// Load Model from path with ASSIMP
void Model::loadModel(const std::string &pPath)
{
    // Use ASSIMP Importer to read file.
    pScene = import.ReadFile(pPath,
        aiProcess_Triangulate | 
        aiProcess_FlipUVs | 
        aiProcess_GenSmoothNormals // | aiProcess_CalcTangentSpace
    );

	// Error check
    if (!pScene || !pScene->mRootNode || pScene->mFlags & AI_SCENE_FLAGS_INCOMPLETE)
    {
        std::cout << "Assimp importer.ReadFile (Error) -- " << import.GetErrorString() << std::endl;
        return;
    }

	// Retrieve the directory path of the filepath.
	directory = pPath.substr(0, pPath.find_last_of("/"));

	// Process ASSIMP's root node recursively.
	processNode(pScene->mRootNode, pScene);
}

/* 
 *  Process a node recursively.
 *  Process each individual mesh located at the node and repeat on the children nodes (if any).
 */
void Model::processNode(aiNode* node, const aiScene* pScene)
{
	// Process all the node's meshes.
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
        /*
        *   The Node Object only contains Indices in order to index the actual objects in the pScene.
        *   The Scene contains all the data. 
        */

		aiMesh* mesh = pScene->mMeshes[node->mMeshes[i]];
		Mesh newMesh = processMesh(mesh, pScene);
		addMesh(&newMesh);
	}

	// Process all children node's meshes.
	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		processNode(node->mChildren[i], pScene);
	}
}


// Process mesh in object file. (Assimp to Mesh)
Mesh Model::processMesh(aiMesh* mesh, const aiScene* pScene)
{
    // Data to fill
    std::vector<Vertex> vertices(mesh->mNumVertices);
    std::vector<unsigned int> indices(3 * mesh->mNumFaces);
    std::vector<MeshTexture> textures;

    // Process Vertices
    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        // Positions
        vertices[i].position = glm::vec3(
            mesh->mVertices[i].x,
            mesh->mVertices[i].y,
            mesh->mVertices[i].z
        );

        // Normals
        if (mesh->HasNormals())
        {
            vertices[i].normal = glm::vec3(
                mesh->mNormals[i].x,
                mesh->mNormals[i].y,
                mesh->mNormals[i].z
            );
        }
        else
        {
            vertices[i].normal = glm::vec3(0.0f);
            std::cout << "MODEL::PROCESS_MESH - No Normals" << std::endl;
        }

        // Texture UV Coordinates
        if (mesh->mTextureCoords[0])
        {
            vertices[i].texCoord = glm::vec2(
                mesh->mTextureCoords[0][i].x,
                mesh->mTextureCoords[0][i].y
            );
        }
        else
        {
            vertices[i].texCoord = glm::vec2(0.0f);
            std::cout << "MODEL::PROCESS_MESH - No Texture UV Coordinates" << std::endl;
        }
    }

    // Process Faces and their Indices
    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];

        // Process Indices 
        for (unsigned int j = 0; j < face.mNumIndices; j++)
        {
            indices.push_back(face.mIndices[j]);
        }
    }

    aiMaterial* material = pScene->mMaterials[mesh->mMaterialIndex];

    // 1. Diffuse Maps
    std::vector<MeshTexture> diffuseMaps = loadTextures(material, aiTextureType_DIFFUSE);
    textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

    // 2. Specular Maps
    std::vector<MeshTexture> specularMaps = loadTextures(material, aiTextureType_SPECULAR);
    textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

    // 3. Normal Maps
    std::vector<MeshTexture> normalMaps = loadTextures(material, aiTextureType_HEIGHT);
    textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());

    // 4. Height Maps
    std::vector<MeshTexture> heightMaps = loadTextures(material, aiTextureType_AMBIENT);
    textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());


    // Return a mesh object created from the extracted mesh data.
    return Mesh(vertices, indices, textures);
}


// Load List of Textures
std::vector<MeshTexture> Model::loadTextures(aiMaterial* mat, aiTextureType type)
{
    std::vector<MeshTexture> textures;

    for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString texPath;
        mat->GetTexture(type, i, &texPath);

        // Prevent duplicate loading.
        bool skip = false;
        for (unsigned int j = 0; j < loadedTextures.size(); j++) 
        {
            if (strcmp(loadedTextures[j].path.data(), texPath.C_Str()) == 0)
            {
                textures.push_back(loadedTextures[j]);
                skip = true; // a texture with the same filepath has already been loaded, continue to next one.
                break;
            }
        }

        // Load Unloaded Texture
        if (!skip)
        {
            MeshTexture tex;
            tex.ID = textureFromFile(texPath.C_Str(), this->directory);
            tex.path = texPath.C_Str();

            // Store texture into vector.
            textures.push_back(tex);

            // Store as loadedTextures for entire model to prevent unnecessary loading of duplicate textures.
            loadedTextures.push_back(tex);
        }
    }

    return textures;
}


// Load texture from path.
unsigned int textureFromFile(const char* path, const std::string& directory)
{
    stbi_set_flip_vertically_on_load(true);

    std::string fileName = std::string(path);

    unsigned int textureID;
    glGenTextures(1, &textureID);

    // Load image from file.
    int width, height, nChannels;
    unsigned char* data = stbi_load((directory + "/" + fileName).c_str(), &width, &height, &nChannels, 0);

    if (data)
    {
        GLenum colorMode = GL_RED;
        switch (nChannels)
        {
        case 1:
            colorMode = GL_RED;
            break;

        case 3:
            colorMode = GL_RGB;
            break;

        case 4:
            colorMode = GL_RGBA;
            break;

        default:
            std::cout << "TEXTURE::LOAD - ERROR - Invalid Format";
            break;
        }

        // Bind Texture
        glBindTexture(GL_TEXTURE_2D, textureID);

        // Set Texture
        glTexImage2D(GL_TEXTURE_2D, 0, colorMode, width, height, 0, colorMode, GL_UNSIGNED_BYTE, data);

        // Generate Mipmap.
        glGenerateMipmap(GL_TEXTURE_2D);

        // Set Params
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // Free the loaded image.
        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture2D failed to load at path: " << directory + "/" + path << std::endl;

        // Free the loaded image.
        stbi_image_free(data);
    }

    return textureID;
}
#pragma once



#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include "mesh.hpp"
#include "shader_program.hpp"

// Forward Declaration
class Window;

/*
	Model Class
*/

unsigned int textureFromFile(const char* path, const std::string& directory);

class Model
{
public:

	// Model ID
	std::string modelID;

	// Mesh List
	std::vector<Mesh> meshes;

	unsigned int numMeshes;

	glm::vec3 pos;
	glm::vec3 size;


	// Constructor
	Model(const std::string &pPath);

	// Destructor
	~Model();


	// Load Model from path
	void loadModel(const std::string &pPath);

	// Add a mesh to the list
	void addMesh(Mesh* mesh);

	// Render meshes
	void render(ShaderProgram &shader);

	void cleanup();


private:

	Assimp::Importer import;

	const aiScene* pScene = nullptr;
	
	aiNode* pRootNode = nullptr;


protected:

	// True if mesh only has materials
	bool noTex;

	// Directory containing object file
	std::string directory;

	// list of loaded textures
	std::vector<MeshTexture> loadedTextures;


	/*
		Model loading functions (ASSIMP)
	*/

	// Process node in object file
	void processNode(aiNode* node, const aiScene* scene);

	// Process Mesh in object file
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);

	// Load list of Textures
	std::vector<MeshTexture> loadTextures(aiMaterial* mat, aiTextureType type);
};
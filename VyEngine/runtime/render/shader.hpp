#pragma once

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <assimp/scene.h>

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "VyLib/vy_logger.hpp"

std::string getFileContents(const char* filePath);

/*
	Shader Struct
*/

struct Shader
{
	GLuint shaderID;

	bool compile(const char* filePath, GLuint type);

	void destroy();
};
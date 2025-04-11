#pragma once

#include "render/shader.hpp"
#include "VyLib/vy_file.hpp"
#include <list>

struct ShaderProgram
{
	GLuint programID;

	void init(const char* vertexShaderPath, const char* fragShaderPath);

	bool generate(const char* vertexShaderPath, const char* fragShaderPath);

	void activate() const;
	
	void deactivate() const;
	
	void destroy();

    
	// Bool
	void setUniform(const std::string& name, bool v);

	// Integer
	void setUniform(const std::string& name, int  v);
	void setUniform(const std::string& name, unsigned int  v);

	// Float
	void setUniform(const std::string& name, float v);
	void setUniform(const std::string& name, float v1, float v2);
	void setUniform(const std::string& name, float v1, float v2, float v3);
	void setUniform(const std::string& name, float v1, float v2, float v3, float v4);

	// GLM Vector
	void setUniform(const std::string& name, glm::vec2 v);
	void setUniform(const std::string& name, glm::vec3 v);
	void setUniform(const std::string& name, glm::vec4 v);

	// Assimp Color
	void setUniform(const std::string& name, aiColor4D color);

	// GLM Matrix
	void setUniform(const std::string& name, glm::mat2 v);
	void setUniform(const std::string& name, glm::mat3 v);
	void setUniform(const std::string& name, glm::mat4 v);
};
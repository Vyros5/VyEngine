#include "shader_program.hpp"


// Activation & Deactivation
void ShaderProgram::activate() const
{
	glUseProgram(programID);
}

void ShaderProgram::deactivate() const
{
	glUseProgram(0);
}

void ShaderProgram::destroy()
{
	if (programID != UINT32_MAX)
	{
		glDeleteProgram(programID);
		programID = UINT32_MAX;
	}
}

void ShaderProgram::init(const char* vertexShaderPath, const char* fragShaderPath)
{
	if (!generate(vertexShaderPath, fragShaderPath))
	{
		std::cout << "Failed to generate the shader program.\n\n";
		destroy();
	}

}


bool ShaderProgram::generate(const char* vertexShaderPath, const char* fragShaderPath)
{
	// Create Shader Program
	GLuint program = glCreateProgram();

	Shader vertShader;
	if (!vertShader.compile(vertexShaderPath, GL_VERTEX_SHADER))
	{
		std::cout << "Failed to compile vertex shader.\n\n";
		vertShader.destroy();
		return false;
	}

	Shader fragShader;
	if (!fragShader.compile(fragShaderPath, GL_FRAGMENT_SHADER))
	{
		std::cout << "Failed to compile fragment shader.\n\n";
		fragShader.destroy();
		return false;
	}

	// Attach the shader to program and delete it.
	glAttachShader(program, vertShader.shaderID);
	glAttachShader(program, fragShader.shaderID);

	// Link Program
	glLinkProgram(program);

	// Catch linking errors.
	GLint isLinked = GL_FALSE;
	glGetProgramiv(program, GL_LINK_STATUS, &isLinked);

	if (!isLinked)
	{
		GLint maxLength = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character.
		std::vector<GLchar> infoLog(maxLength);
		glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

		// Delete Program and Shaders.
		glDeleteProgram(program);
		vertShader.destroy();
		fragShader.destroy();
		
		std::cout << "Shader Linking Failed: " << infoLog.data() << std::endl;
		programID = UINT32_MAX;
		return false;
	}
	
	// Always detach shaders after a successful link and destroy them since we don't need them anymore.
	glDetachShader(program, vertShader.shaderID);
	glDetachShader(program, fragShader.shaderID);
	vertShader.destroy();
	fragShader.destroy();
	
	// Set program.
	programID = program;
	std::cout << "Shader compilation and linking succeeded:\n";
	std::cout << "<Vertex:   " << vertexShaderPath << ">\n";
	std::cout << "<Fragment: " << fragShaderPath << ">\n\n";

	return true;
}



// Bool
void ShaderProgram::setUniform(const std::string& name, bool v)
{
	glUniform1i(glGetUniformLocation(programID, name.c_str()), (int)v);
}


// Integer
void ShaderProgram::setUniform(const std::string& name, int  v)
{
	glUniform1i(glGetUniformLocation(programID, name.c_str()), v);
}

void ShaderProgram::setUniform(const std::string& name, unsigned int  v)
{
	glUniform1i(glGetUniformLocation(programID, name.c_str()), v);
}


// Float
void ShaderProgram::setUniform(const std::string& name, float v)
{
	glUniform1f(glGetUniformLocation(programID, name.c_str()), v);
}

void ShaderProgram::setUniform(const std::string& name, float v1, float v2)
{
	glUniform2f(glGetUniformLocation(programID, name.c_str()), v1, v2);
}

void ShaderProgram::setUniform(const std::string& name, float v1, float v2, float v3)
{
	glUniform3f(glGetUniformLocation(programID, name.c_str()), v1, v2, v3);
}

void ShaderProgram::setUniform(const std::string& name, float v1, float v2, float v3, float v4)
{
	glUniform4f(glGetUniformLocation(programID, name.c_str()), v1, v2, v3, v4);
}


// GLM Vector
void ShaderProgram::setUniform(const std::string& name, glm::vec2 v)
{
	glUniform2f(glGetUniformLocation(programID, name.c_str()), v.x, v.y);
}

void ShaderProgram::setUniform(const std::string& name, glm::vec3 v)
{
	glUniform3f(glGetUniformLocation(programID, name.c_str()), v.x, v.y, v.z);
}

void ShaderProgram::setUniform(const std::string& name, glm::vec4 v)
{
	glUniform4f(glGetUniformLocation(programID, name.c_str()), v.x, v.y, v.z, v.w);
}


// Assimp Color
void ShaderProgram::setUniform(const std::string& name, aiColor4D v)
{
	glUniform4f(glGetUniformLocation(programID, name.c_str()), v.r, v.g, v.b, v.a);
}


// GLM Matrix
void ShaderProgram::setUniform(const std::string& name, glm::mat2 v)
{
	glUniformMatrix2fv(glGetUniformLocation(programID, name.c_str()), 1, GL_FALSE, value_ptr(v));
}

void ShaderProgram::setUniform(const std::string& name, glm::mat3 v)
{
	glUniformMatrix3fv(glGetUniformLocation(programID, name.c_str()), 1, GL_FALSE, value_ptr(v));
}

void ShaderProgram::setUniform(const std::string& name, glm::mat4 v)
{
	glUniformMatrix4fv(glGetUniformLocation(programID, name.c_str()), 1, GL_FALSE, value_ptr(v));
}
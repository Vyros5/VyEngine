#include "render/shader.hpp"

// Reads file and returns a string of it's contents.
std::string getFileContents(const char* filePath)
{
    std::string contents;
    std::ifstream in(filePath, std::ios::in | std::ios::binary);

    if (in)
    {
        in.seekg(0, std::ios::end);
        contents.resize(in.tellg());
        in.seekg(0, std::ios::beg);
        in.read(&contents[0], contents.size());
        in.close();
    }
    else
    {
        VY_LOG_ERROR("Couldn't open file: '&s'", filePath);
    }

    return(contents);
}


bool Shader::compile(const char* filePath, GLuint type)
{
    std::cout << "Compiling shader: " << filePath << std::endl;

    // Get shader contents from file.
    std::string shaderCode = getFileContents(filePath);

    // Convert string into character array.
    const char* shaderContents = shaderCode.c_str();

    // Create an empty shader.(Allocate)
    shaderID = glCreateShader(type);

    // Attach contents to shader.
    glShaderSource(shaderID, 1, &shaderContents, nullptr);

    // Compile Shader into machine code.
    glCompileShader(shaderID);

    // Catch Compilation errors.
    GLint isCompiled = 0;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &isCompiled);
    if (!isCompiled)
    {
        GLint maxLength = 0;
        glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &maxLength);

        // The maxLength includes the NULL character.
        std::vector<GLchar> infoLog(maxLength);
        glGetShaderInfoLog(shaderID, maxLength, &maxLength, &infoLog[0]);

        // Delete the shader.
        glDeleteShader(shaderID);
        std::cout << "Shader Compilation Failed: " << infoLog.data() << std::endl;

        shaderID = UINT32_MAX;
        return false;
    }
    else
    {
        std::cout << "Successfully Compiled\n\n";
    }

    return true;
}

void Shader::destroy()
{
    if (shaderID != UINT32_MAX)
    {
        glDeleteShader(shaderID);
        shaderID = UINT32_MAX;
    }
}
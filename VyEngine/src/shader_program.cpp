#include <shader_program.hpp>



ShaderProgram::ShaderProgram()
{
    programID = 0;
}

ShaderProgram::~ShaderProgram()
{
    // Delete the intermediate shader objects that have been added to the program
    // The list will only contain something if shaders were compiled but the object itself
    // was destroyed prior to linking.

    for (ShaderObjList::iterator it = shaderList.begin(); it != shaderList.end(); it++)
    {
        glDeleteShader(*it);
    }

    if (programID != 0)
    {
        glDeleteProgram(programID);
        programID = 0;
    }
}

bool ShaderProgram::init()
{
    programID = glCreateProgram();

    if (programID == 0)
    {
        fprintf(stderr, "Error creating shader program\n");
        return false;
    }

    return true;
}

// Used to add shaders to the program. When finished - call finalize()
bool addShader(GLenum shaderType, const char* pFilename)
{
    std::string s;

    if (!ReadFile(pFilename, s))
    {
        return false;
    }

    Shader shader;
}

bool finalize()
{

}

GLuint getUniformLocation(const char* pUniformName)
{

}
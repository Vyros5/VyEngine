#pragma once

#include <shader.hpp>
#include <vy_file.hpp>
#include <list>

class ShaderProgram
{
public:

    ShaderProgram();

    ~ShaderProgram();

    bool init();

    void enable();

    GLuint getProgram() const { return programID; }

protected:

    bool addShader(GLenum shaderType, const char* pFilename);

    bool finalize();

    GLuint getUniformLocation(const char* pUniformName);

    GLuint programID;

private:

    typedef std::list<GLuint> ShaderObjList;

    ShaderObjList shaderList;
};



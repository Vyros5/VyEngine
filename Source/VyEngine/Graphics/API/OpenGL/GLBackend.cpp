#include "Graphics/API/OpenGL/GLBackend.hpp"

#include "Support/Logger/LogDef.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>


void GLDebugMessageCallback(uint32_t source, uint32_t type, uint32_t id, uint32_t severity, int32_t length, const char* message, const void* userParam)
{
	// ignore non-significant error/warning codes
	if (id == 131169 || id == 131185 || id == 131218 || id == 131204) return;

	std::string output;

	output += "OpenGL Debug Message:\n";
	output += "Debug message (" + std::to_string(id) + "): " + message + "\n";

	switch (source)
	{
	case GL_DEBUG_SOURCE_API:				output += "Source: API";                break;
	case GL_DEBUG_SOURCE_WINDOW_SYSTEM:		output += "Source: Window System";      break;
	case GL_DEBUG_SOURCE_SHADER_COMPILER:	output += "Source: Shader Compiler";    break;
	case GL_DEBUG_SOURCE_THIRD_PARTY:		output += "Source: Third Party";        break;
	case GL_DEBUG_SOURCE_APPLICATION:		output += "Source: Application";        break;
	case GL_DEBUG_SOURCE_OTHER:				output += "Source: Other";              break;
	}

	output += "\n";

	switch (type)
	{
	case GL_DEBUG_TYPE_ERROR:               output += "Type: Error";                break;
	case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: output += "Type: Deprecated Behavior";  break;
	case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  output += "Type: Undefined Behavior";   break;
	case GL_DEBUG_TYPE_PORTABILITY:         output += "Type: Portability";          break;
	case GL_DEBUG_TYPE_PERFORMANCE:         output += "Type: Performance";          break;
	case GL_DEBUG_TYPE_MARKER:              output += "Type: Marker";               break;
	case GL_DEBUG_TYPE_PUSH_GROUP:          output += "Type: Push Group";           break;
	case GL_DEBUG_TYPE_POP_GROUP:           output += "Type: Pop Group";            break;
	case GL_DEBUG_TYPE_OTHER:               output += "Type: Other";                break;
	}

	output += "\n";

	switch (severity)
	{
	case GL_DEBUG_SEVERITY_HIGH:			output += "Severity: High";             break;
	case GL_DEBUG_SEVERITY_MEDIUM:			output += "Severity: Medium";           break;
	case GL_DEBUG_SEVERITY_LOW:				output += "Severity: Low";              break;
	case GL_DEBUG_SEVERITY_NOTIFICATION:	output += "Severity: Notification";     break;
	}

	switch (severity)
	{
	case GL_DEBUG_SEVERITY_HIGH:			VYERROR(output);      break;
	case GL_DEBUG_SEVERITY_MEDIUM:			VYWARN(output);       break;
	case GL_DEBUG_SEVERITY_LOW:				VYINFO(output);       break;
	case GL_DEBUG_SEVERITY_NOTIFICATION:	VYINFO(output);       break;
	}
}

bool GetBool(uint32_t parameter)
{
    GLboolean result;
    glGetBooleanv(parameter, &result);
    return static_cast<bool>(result);
}

bool GetBool(uint32_t parameter, uint32_t index)
{
    GLboolean result;
    glGetBooleani_v(parameter, index, &result);
    return static_cast<bool>(result);
}

int GetInt(uint32_t parameter)
{
    GLint result;
    glGetIntegerv(parameter, &result);
    return static_cast<int>(result);
}

int GetInt(uint32_t parameter, uint32_t index)
{
    GLint result;
    glGetIntegeri_v(parameter, index, &result);
    return static_cast<int>(result);
}

float GetFloat(uint32_t parameter)
{
    GLfloat result;
    glGetFloatv(parameter, &result);
    return static_cast<float>(result);
}

float GetFloat(uint32_t parameter, uint32_t index)
{
    GLfloat result;
    glGetFloati_v(parameter, index, &result);
    return static_cast<float>(result);
}

double GetDouble(uint32_t parameter)
{
    GLdouble result;
    glGetDoublev(parameter, &result);
    return static_cast<double>(result);
}

double GetDouble(uint32_t parameter, uint32_t index)
{
    GLdouble result;
    glGetDoublei_v(parameter, index, &result);
    return static_cast<double>(result);
}

int64_t GetInt64(uint32_t parameter)
{
    GLint64 result;
    glGetInteger64v(parameter, &result);
    return static_cast<int64_t>(result);
}

int64_t GetInt64(uint32_t parameter, uint32_t index)
{
    GLint64 result;
    glGetInteger64i_v(parameter, index, &result);
    return static_cast<int64_t>(result);
}

std::string GetString(uint32_t parameter)
{
    const GLubyte* result = glGetString(parameter);
    return result ? reinterpret_cast<const char*>(result) : std::string();
}

std::string GetString(uint32_t parameter, uint32_t index)
{
    const GLubyte* result = glGetStringi(parameter, index);
    return result ? reinterpret_cast<const char*>(result) : std::string();
}

namespace VyEngine::GFX::API
{
    void GLBackend::Init(bool isDebug)
    {
        // Load OpenGL functions, gladLoadGL returns the loaded version, 0 on error.
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
            VYERROR("Failed to initialize GLAD OpenGL context!");
			exit(EXIT_FAILURE);
		}

        VYINFO("[Initialized GLAD]");

        if (isDebug)
        {
            glEnable(GL_DEBUG_OUTPUT);
            glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
            glDebugMessageCallback(GLDebugMessageCallback, nullptr);
        }
    }

    // void GLBackend::OnFrameStarted()
    // {
    //
    // }
    //
    // void GLBackend::OnFrameCompleted()
    // {
    //
    // }

    void GLBackend::ClearBuffers(bool colorBuffer, bool depthBuffer, bool stencilBuffer)
    {
        GLbitfield clearMask = 0;
        if (colorBuffer)   { clearMask |= GL_COLOR_BUFFER_BIT;   }
        if (depthBuffer)   { clearMask |= GL_DEPTH_BUFFER_BIT;   }
        if (stencilBuffer) { clearMask |= GL_STENCIL_BUFFER_BIT; }

        if (clearMask != 0)
        {
            glClear(clearMask);
        }
    }

    // void GLBackend::ReadPixels(uint32_t X, uint32_t Y, uint32_t width, uint32_t height, GLenum format, EPixelDataType type, void* data)
    // {

    // }

    void GLBackend::DrawElements(GLenum primitiveMode, uint32_t indexCount)
    {
        glDrawElements(primitiveMode, indexCount, GL_UNSIGNED_INT, nullptr);
    }

    void GLBackend::DrawElementsInstanced(GLenum primitiveMode, uint32_t indexCount, uint32_t instances)
    {
        glDrawElementsInstanced(primitiveMode, indexCount, GL_UNSIGNED_INT, nullptr, instances);
    }

    void GLBackend::DrawArrays(GLenum primitiveMode, uint32_t vertexCount)
    {
        glDrawArrays(primitiveMode, 0, vertexCount);
    }

    void GLBackend::DrawArraysInstanced(GLenum primitiveMode, uint32_t vertexCount, uint32_t instances)
    {
        glDrawArraysInstanced(primitiveMode, 0, vertexCount, instances);
    }

    void GLBackend::SetClearColor(float r, float g, float b, float a)
    {
        glClearColor(r, g, b, a);
    }

    void GLBackend::SetRasterizationMode(GLenum rasterizationMode)
    {
        glPolygonMode(GL_FRONT_AND_BACK, rasterizationMode);
    }

    void GLBackend::SetRasterizationLinesWidth(float width)
    {
        glLineWidth(width);
    }

    void GLBackend::SetCapability(GLenum capability, bool value)
    {
        (value ? glEnable : glDisable)(capability);
    }

    bool GLBackend::GetCapability(GLenum capability)
    {
        return glIsEnabled(capability);
    }

    void GLBackend::SetStencilAlgorithm(GLenum algorithm, int32_t reference, uint32_t mask)
    {
        glStencilFunc(algorithm, reference, mask);
    }

    void GLBackend::SetDepthAlgorithm(GLenum algorithm)
    {
        glDepthFunc(algorithm);
    }

    void GLBackend::SetStencilMask(uint32_t mask)
    {
        glStencilMask(mask);
    }

    void GLBackend::SetStencilOperations(GLenum stencilFail, GLenum depthFail, GLenum bothPass)
    {
        glStencilOp(stencilFail, depthFail, bothPass);
    }

    void GLBackend::SetCullFace(GLenum cullFace)
    {
        glCullFace(cullFace);
    }

    void GLBackend::SetDepthWriting(bool enable)
    {
        glDepthMask(enable);
    }

    void GLBackend::SetColorWriting(bool enableRed, bool enableGreen, bool enableBlue, bool enableAlpha)
    {
        glColorMask(enableRed, enableGreen, enableBlue, enableAlpha);
    }

    void GLBackend::SetViewport(uint32_t X, uint32_t Y, uint32_t width, uint32_t height)
    {
        glViewport(X, Y, width, height);
    }

    std::string GLBackend::GetVendor()
    {
        return GetString(GL_VENDOR);
    }

    std::string GLBackend::GetHardware()
    {
        return GetString(GL_RENDERER);
    }

    std::string GLBackend::GetVersion()
    {
        return GetString(GL_VERSION);
    }

    std::string GLBackend::GetShadingLanguageVersion()
    {
        return GetString(GL_SHADING_LANGUAGE_VERSION);
    }
}
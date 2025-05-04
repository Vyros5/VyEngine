#include "Window/Device/Device.h"

#include <GLFW/glfw3.h>
#include "Support/Logger/LogDef.h"


namespace VyEngine::Window::Context
{
    Device::Device(const Cfg::DeviceConfig& deviceConfig)
    {
        int success = glfwInit();
        if (success == GLFW_FALSE)
        {
            VYCRITICAL("Failed to initialize GLFW!")
            glfwTerminate();
        }

        CreateCursors();

        if (deviceConfig.debugProfile)
        {
            VYINFO("OpenGL Context: Debug Profile Enabled")
            glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, deviceConfig.majorVersion);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, deviceConfig.minorVersion);

        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_SAMPLES, deviceConfig.samples);

        m_IsAlive = true;

        VYINFO("[Initialized GLFW]");
    }

    Device::~Device()
    {
        if (m_IsAlive)
        {
            VYINFO("Terminating GLFW...");
            DestroyCursors();
            glfwTerminate();
        }
    }

    std::pair<int16_t, int16_t> Device::GetMonitorSize() const
    {
        const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
        return std::pair<int16_t, int16_t>(static_cast<int16_t>(mode->width), static_cast<int16_t>(mode->height));
    }


    std::array<int, 4> Device::GetWorkAreaSize() const
    {
        std::array<int, 4> workArea;

        glfwGetMonitorWorkarea(
            glfwGetPrimaryMonitor(),
            workArea.data(),     // xPos
            workArea.data() + 1, // yPos
            workArea.data() + 2, // width
            workArea.data() + 3  // height
        );

        return workArea;
    }


    GLFWcursor* Device::GetCursorInstance(Data::ECursorType cursorType) const
    {
        return m_Cursors.at(cursorType);
    }


    bool Device::HasVSync() const
    {
        return m_IsVSync;
    }


    void Device::SetVSync(bool value)
    {
        glfwSwapInterval(value ? 1 : 0);
        m_IsVSync = value;
    }


    void Device::PollEvents() const
    {
        glfwPollEvents();
    }


    float Device::GetElapsedTime() const
    {
        return static_cast<float>(glfwGetTime());
    }


    void Device::BindErrorCallback()
    {

    }


    void Device::CreateCursors()
    {
        m_Cursors[Data::ECursorType::ARROW]     = glfwCreateStandardCursor(static_cast<int>(Data::ECursorType::ARROW));
        m_Cursors[Data::ECursorType::IBEAM]     = glfwCreateStandardCursor(static_cast<int>(Data::ECursorType::IBEAM));
        m_Cursors[Data::ECursorType::CROSSHAIR] = glfwCreateStandardCursor(static_cast<int>(Data::ECursorType::CROSSHAIR));
        m_Cursors[Data::ECursorType::HAND]      = glfwCreateStandardCursor(static_cast<int>(Data::ECursorType::HAND));
        m_Cursors[Data::ECursorType::HRESIZE]   = glfwCreateStandardCursor(static_cast<int>(Data::ECursorType::HRESIZE));
        m_Cursors[Data::ECursorType::VRESIZE]   = glfwCreateStandardCursor(static_cast<int>(Data::ECursorType::VRESIZE));
    }
    
    void Device::DestroyCursors()
    {
        glfwDestroyCursor(m_Cursors[Data::ECursorType::ARROW]);
        glfwDestroyCursor(m_Cursors[Data::ECursorType::IBEAM]);
        glfwDestroyCursor(m_Cursors[Data::ECursorType::CROSSHAIR]);
        glfwDestroyCursor(m_Cursors[Data::ECursorType::HAND]);
        glfwDestroyCursor(m_Cursors[Data::ECursorType::HRESIZE]);
        glfwDestroyCursor(m_Cursors[Data::ECursorType::VRESIZE]);
    }
}
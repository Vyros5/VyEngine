#include "gl_window.hpp"

#include "render/graphics_context.hpp"
#include "VyLib/vy_logger.hpp"
#include "event/event_manager.hpp"
#include "event/events/app_event.hpp"
#include "event/events/key_event.hpp"
#include "event/events/mouse_event.hpp"

#include <GLFW/glfw3.h>
#include <iostream>

namespace VyEngine
{
    namespace
    {
        uint16_t GLFWwindowCount = 0;
    }

    static void GLFWErrorCallback(int err, const char* desc)
    {

    }


    OpenGLWindow::OpenGLWindow(const WindowProps& props)
    {
        Init(props);
    }

    OpenGLWindow::~OpenGLWindow()
    {
        Shutdown();
    }


    void OpenGLWindow::Init(const WindowProps& props)
    {
        mData.Title = props.Title;
        mData.Width = props.Width;
        mData.Height = props.Height;
        mData.VSync = props.IsVSync;
        mData.Fullscreen = props.IsFullscreen;

        if (GLFWwindowCount == 0)
        {
            int success = glfwInit();
            glfwSetErrorCallback(GLFWErrorCallback);
            if (!success)
            {
                std::cout << "Failed to initialize GLFW\n";
                exit(0);
            }
        }

        int major, minor, rev;
		glfwGetVersion(&major, &minor, &rev);
        VY_CORE_INFO("GLFW v{}.{}.{} Initialized", major, minor, rev);
		// std::cout << "[GLFW v" << major << "." << minor << "." << rev << " Initialized]\n";

        // Version
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);

		// Profile
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        // ========================================================================================

        mMonitor = glfwGetPrimaryMonitor();

        if (mData.Fullscreen)
        {
            const GLFWvidmode* mode = glfwGetVideoMode(mMonitor);

            mData.Width = mode->width;
            mData.Height = mode->height;
        }

        // ========================================================================================
        VY_CORE_INFO("Creating window {} ({}, {})", props.Title, props.Width, props.Height);

        mWindow = glfwCreateWindow(mData.Width, mData.Height, mData.Title.c_str(), mData.Fullscreen ? mMonitor : nullptr, nullptr);
        
		if (!mWindow)
		{
			const char* pDesc = NULL;
			int err = glfwGetError(&pDesc);
			std::cout << "Failed to create GLFW window: " << pDesc << " : " << err <<"\n";
			exit(1);
		}
        ++GLFWwindowCount;

        // ========================================================================================

        mContext = GraphicsContext::Create(mWindow);
        mContext->Init();

        glfwSetWindowUserPointer(mWindow, &mData);
        SetVSync(mData.VSync);

        // ========================================================================================

        // Set GLFW Callbacks
        
    }


    void OpenGLWindow::OnUpdate()
    {
        mContext->SwapBuffers();
        glfwPollEvents();
    }

    void OpenGLWindow::SetVSync(bool enabled)
    {
        if (enabled)
            glfwSwapInterval(1);
        else
            glfwSwapInterval(0);

        mData.VSync = enabled;
    }

    bool OpenGLWindow::IsVSync() const
    {
        return mData.VSync;
    }


    void OpenGLWindow::SetFullscreen(bool enabled)
    {
        if (mData.Fullscreen != enabled)
        {
            mData.Fullscreen = enabled;

            if (enabled)
            {
                const GLFWvidmode* mode = glfwGetVideoMode(mMonitor);

                mData.Width = mode->width;
                mData.Height = mode->height;
                glfwSetWindowMonitor(mWindow, mMonitor, 0, 0, mData.Width, mData.Height, mode->refreshRate);
            }
            else
            {
                // mData.Width = 
            }

            // Trigger Event
            Events::Trigger(Events::WindowResizeEvent(mData.Width, mData.Height));
        }
    }

    bool OpenGLWindow::IsFullscreen() const
    {
        return mData.Fullscreen;
    }


    void OpenGLWindow::Shutdown()
    {
        glfwDestroyWindow(mWindow);
        --GLFWwindowCount;

        if (GLFWwindowCount == 0)
            glfwTerminate();
    }
}
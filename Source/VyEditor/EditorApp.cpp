#include "EditorApp.h"


namespace Editor
{
    EditorApplication::EditorApplication(Context* context) : 
        VyApplication(context)
    {
        VYTRACE("Created EditorApplication")
    }

    EditorApplication::~EditorApplication()
    {
        VYTRACE("Destroyed EditorApplication")
    }

    void EditorApplication::Run()
    {
        VYTRACE("Start Run")

        while (Isrunning())
        {
            m_Context->gfxDriver->ClearBuffer(true, false, false);
            m_Context->window->SwapBuffers();
            m_Context->displayDevice->PollEvents();
        }

        VYTRACE("End Run")
    }
}
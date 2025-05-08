
#include <string>
#include <iostream>
#include <filesystem>
#include <Core/Base.h>
#include <Core/Context.h>
#include <Support/Logger/LogDef.h>
#include <App/MainLoop.cpp>
#include "Editor/EditorApp.h"

using namespace VyEngine;
using namespace Editor;
using namespace VyEngine::Support;


Context* g_Context = nullptr;


int EntryPoint(int argc, char* argv[])
{
    std::filesystem::path srcDir{R"(C:\dev\cpp\Projects\VyEngine\Source)"};
    
    LogConfig logCfg;
    Logger::Init(logCfg, srcDir.string());

    Context* context = new Context();
    EditorApplication* app = new EditorApplication(context);

    try
    {
        app->Run();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    delete app;

    return 0;
}


int main(int argc, char* argv[])
{
    return EntryPoint(argc, argv);
}
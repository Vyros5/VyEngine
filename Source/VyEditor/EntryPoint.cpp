
#include <string>
#include <iostream>
#include <filesystem>
#include <Core/Base.h>
#include <Support/Logger/LogDef.h>
#include "EditorApplication.h"
#include <Core/Context.h>
using namespace VyEngine;
using namespace VyEditor;
using namespace VyEngine::Support;


Context* g_Context = nullptr;


int EntryPoint(int argc, char* argv[])
{
    std::filesystem::path srcDir{R"(C:\dev\cpp\Projects\VyEngine\Source)"};
    
    LogConfig logCfg;
    Logger::Init(logCfg, srcDir.string());

    Context* context = new Context();
    EditorApplication* app = new EditorApplication(context);

    return app->Run();
}


int main(int argc, char* argv[])
{
    for (int i = 0; i < argc; i++)
    {
        std::cout << argv[i] << std::endl;
    }

    return EntryPoint(argc, argv);
}
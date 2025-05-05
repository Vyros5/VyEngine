
#include <string>
#include <iostream>
#include <filesystem>
#include <Core/Base.h>
#include <Support/Logger/LogDef.h>
#include "Application.hpp"
#include <Core/Context.h>
using namespace VyEngine;
using namespace VyEngine::Support;


Context* g_Context = nullptr;


int EntryPoint(int argc, char* argv[])
{
    namespace fs = std::filesystem;
    fs::path srcDir{R"(C:\dev\cpp\Projects\VyEngine\Source)"};
    
    LogConfig logCfg;
    Logger::Init(logCfg, srcDir.string());

    std::cout << "File Source Dir: " << srcDir.string() << std::endl;

    // Ref<Context> context = MakeRef<Context>();
    SharedPtr<Context> context(new Context());
    g_Context = context;

    VyEditor::Application app(g_Context);



    return 0;
}


int main(int argc, char* argv[])
{
    for (int i = 0; i < argc; i++)
    {
        std::cout << argv[i] << std::endl;
    }

    return EntryPoint(argc, argv);
}
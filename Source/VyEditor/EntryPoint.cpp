
#include <string>
#include <iostream>
#include <filesystem>
#include <Core/Base.h>
#include <Support/Logger/LogDef.h>

using namespace VyEngine;
using namespace VyEngine::Support;
int EntryPoint(int argc, char* argv[])
{
    namespace fs = std::filesystem;
    fs::path srcDir{R"(C:\dev\cpp\Projects\VyEngine\Source)"};
    
    LogConfig logCfg;
    Logger::Init(logCfg, srcDir.string());

    std::cout << "File Source Dir: " << srcDir.string() << std::endl;

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
#include <VyLib/vy_file.hpp>

bool ReadFile(const char* pFileName, std::string& outFile)
{
    std::ifstream f(pFileName);
    bool finished = false;

    if (f.is_open())
    {
        std::string line;
        while(std::getline(f, line))
        {
            outFile.append(line);
            outFile.append("\n");
        }

        f.close();
        finished = true;
    }
    else
    {
        std::cout << "Error reading file: " << pFileName << std::endl;
    }

    return finished;
}

// char* ReadBinaryFile(const char* pFilename, int& size)
// {

// }

// void WriteBinaryFile(const char* pFilename, const void* pData, int size)
// {

// }

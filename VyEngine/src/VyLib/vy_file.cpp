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

// Returns a pointer to a buffer with the contents of the file.
// As well as the size of the file.
char* ReadBinaryFile(const char* pFilename, int& size)
{
    FILE* f = NULL;

    errno_t err = fopen_s(&f, pFilename, "rb");
    
    if (!f)
    {
        char buf[256] = { 0 };
        strerror_s(buf, sizeof(buf), err);
        printf("Error opening '%s': %s", pFilename, buf);
        exit(0);
    }

    struct stat statBuffer;
    int error = stat(pFilename, &statBuffer);

    if (error)
    {
        char buf[256] = { 0 };
        strerror_s(buf, sizeof(buf), err);
        printf("Error getting file stats: %s", buf);
        return NULL;
    }

    size = statBuffer.st_size;

    // Read contents into the buffer that's allocated according to the size.
    char* pCont = (char*)malloc(size);
    assert(pCont);

    size_t bytesRead = fread(pCont, 1, size, f);

    if (bytesRead != size)
    {
        char buf[256] = { 0 };
        strerror_s(buf, sizeof(buf), err);
        printf("Read file error: %s", buf);
        exit(0);
    }

    fclose(f);

    return pCont;
}

void WriteBinaryFile(const char* pFilename, const void* pData, int size)
{
    FILE* f = NULL;
    
    errno_t err = fopen_s(&f, pFilename, "wb");

    if (!f)
    {
        printf("Error opening '%s'", pFilename);
        exit(0);
    }

    int bytesWritten = fwrite(pData, 1, size, f);

    if (bytesWritten != size)
    {
        char buf[256] = { 0 };
        strerror_s(buf, sizeof(buf), err);
        printf("Write file error: %s", buf);
        exit(0);
    }

    fclose(f);
}

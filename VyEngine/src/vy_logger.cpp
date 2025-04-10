#include <vy_logger.hpp>


void VyLogError(const char* pFileName, unsigned int line, const char* pFormat, ...)
{
    char msg[512];
    va_list args;
    va_start(args, pFormat);
    vsnprintf(msg, sizeof(msg), pFormat, args);
    va_end(args);

    #ifdef _WIN32
        char msg2[512];
        _snprintf_s(msg2, sizeof(msg2), "%s:%d: %s", pFileName, line, msg);
        // MessageBoxA(NULL, msg2, NULL, 0);
    #else
        fprintf(stderr, "%s:%d - %s", pFileName, line, msg);
    #endif
}

void VyLogFileError(const char* pFileName, unsigned int line, const char* pFileError)
{
    #ifdef _WIN32
        char msg[1000];
        _snprintf_s(msg, sizeof(msg), "%s:%d: unable to open file `%s`", pFileName, line, pFileError);
        // MessageBoxA(NULL, msg, NULL, 0);
    #else
        fprintf(stderr, "%s:%d: unable to open file `%s`\n", pFileName, line, pFileError);
    #endif
}
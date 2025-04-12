#include <VyLib/vy_logger.hpp>

namespace VyLib
{
    std::vector<LogCmd> logs;
    std::string logFileName = "log.txt";
    ILogger* logger         = nullptr;
    bool logToFile          = true;




    void Log::VyLog(const char* pText, const LogType type)
    {
        if (pText == nullptr)
        {
            std::printf("[VyLog] - Text is null");
        }

        // Lock Mutex
        static std::mutex logMutex;
        std::lock_guard<std::mutex> lock(logMutex);

        // Add time to text.
        time_t t = std::time(nullptr);
        std::tm tm = *std::localtime(&t);

        std::ostringstream oss;
        oss << std::put_time(&tm, "[%H:%M:%S]");
        const std::string text = oss.str() + ": " + std::string(pText);

        if (logger)
        {
            logger->Log(text, static_cast<uint32_t>(type));
        }
    }
    
    void Log::VyLogInfo(const char* pText, ...)
    {
        char buffer[1024];
        va_list args;
        va_start(args, pText);
        auto w = vsnprintf(buffer, sizeof(buffer), pText, args);
        va_end(args);

        VyLog(buffer, LogType::Info);
    }
    
    void Log::VyLogError(const char* pText, ...)
    {
        char buffer[1024];
        va_list args;
        va_start(args, pText);
        auto w = vsnprintf(buffer, sizeof(buffer), pText, args);
        va_end(args);

        VyLog(buffer, LogType::Warning);
    }
    
    void Log::VyLogWarning(const char* pText, ...)
    {
        char buffer[1024];
        va_list args;
        va_start(args, pText);
        auto w = vsnprintf(buffer, sizeof(buffer), pText, args);
        va_end(args);

        VyLog(buffer, LogType::Warning);
    }
    
    
    void Log::VyLog(const std::string& text, const LogType type)
    {
        VyLog(text.c_str(), type);
    }
    
    void Log::VyLogInfo(const std::string text, ...)
    {
        char buffer[2048];
        va_list args;
        va_start(args, text);
        auto w = vsnprintf(buffer, sizeof(buffer), text.c_str(), args);
        va_end(args);

        VyLog(buffer, LogType::Info);
    }
    
    void Log::VyLogError(const std::string text, ...)
    {
        char buffer[2048];
        va_list args;
        va_start(args, text);
        auto w = vsnprintf(buffer, sizeof(buffer), text.c_str(), args);
        va_end(args);

        VyLog(buffer, LogType::Error);
    }
    
    void Log::VyLogWarning(const std::string text, ...)
    {
        char buffer[2048];
        va_list args;
        va_start(args, text);
        auto w = vsnprintf(buffer, sizeof(buffer), text.c_str(), args);
        va_end(args);

        VyLog(buffer, LogType::Warning);
    }
}







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
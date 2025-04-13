#include "vy_logger.hpp"
#include "vy_log_data.hpp"

namespace VyLib
{
    void Logger::HandleErrors(LogType type)
    {
        if ((type >= LogType::ERROR) && Logger::IsStackTraceOnError())
        {
            if(Logger::IsLogToConsole())
                PrintStackTrace(std::cout);

            if (Logger::IsLogToFile())
                PrintStackTrace(logger->logFile);
        }
    }
    
    void Logger::HandleFatalErrors(LogType type)
    {
        Logger::CloseLogFile();
        std::cout.flush();
        AbortApplication();

    }

    const char* Logger::GetLogTypeString(LogType type)
    {
        switch (type)
        {
        case LogType::DEBUG:
            return "  DEBUG";
        case LogType::INFO:
            return "   INFO";
        case LogType::WARNING:
            return "WARNING";
        case LogType::ERROR:
            return "  ERROR";
        case LogType::FATAL:
            return "  FATAL";
        default:
            return "UNNAMED";
        }
    }

    void Logger::Init()
    {
        logger = new LoggerData();
    }

    LoggerData* Logger::GetLog()
    {
        return logger;
    }

    void Logger::Clone(LoggerData* data)
    {
        logger = data;
    }

    void Logger::OpenLogFile(const char* filename)
    {
        Logger::CloseLogFile();
        logger->logFile.open(filename, std::ios::out);
    }

    void Logger::OpenLogFileAppend(const char* filename)
    {
        Logger::CloseLogFile();
        logger->logFile.open(filename, std::ios::out | std::ios::app);
    }

    void Logger::CloseLogFile()
    {
        logger->logFile.close();
    }

    bool Logger::IsLogToConsole()
    {
        return logger->logToConsole;
    }

    bool Logger::IsLogToFile()
    {
        return logger->logToFile;
    }

    bool Logger::IsLogFileOpened()
    {
        return logger->logFile.is_open();
    }

    bool Logger::IsAbortOnFatal()
    {
        return logger->abortOnFatal;
    }

    bool Logger::IsStackTraceOnError()
    {
        return logger->stackTraceOnError;
    }

    void Logger::LogToConsole(const char* text)
    {
        if (Logger::IsLogToConsole())
        {
            std::cout << text;
            std::cout.flush();
        }
    }

    void Logger::LogToFile(const char* text)
    {
        if (Logger::IsLogToFile())
        {
            logger->logFile << text;
            logger->logFile.flush();
        }
    }

    void Logger::LogLineToConsole(const char* text)
    {
        if (Logger::IsLogToConsole())
        {
            std::cout << text << '\n';
            std::cout.flush();
        }
    }

    void Logger::LogLineToFile(const char* text)
    {
        if (Logger::IsLogToFile())
        {
            logger->logFile << text << '\n';
            logger->logFile.flush();
        }
    }

    void Logger::Log(LogType type, const char* text, ...)
    {
        if ((uint8_t)type >= (uint8_t)Logger::GetLogLevel())
        {
            SetConsoleColor(logger->colors[(size_t)type]);
            Logger::LogLineToConsole(text);
            SetConsoleColor(ConsoleColor::GRAY);

            Logger::LogToFile(Logger::GetLogTypeString(type));
            Logger::LogToFile(" > ");
            Logger::LogLineToFile(text);

            Logger::HandleErrors(type);
            Logger::HandleFatalErrors(type);
        }
    }

    void Logger::Log(LogType type, const std::string& caller, const std::string& message)
    {
        auto text = '[' + GetCurrentTime() + ' ' + caller + "]: " + message;
        Logger::Log(type, text.c_str());
    }

    void Logger::SetAbortOnFatal(bool value)
    {
        logger->abortOnFatal = value;
    }

    void Logger::SetStackTraceOnError(bool value)
    {
        logger->stackTraceOnError = value;
    }

    void Logger::SetLogConsole(bool value)
    {
        logger->logToConsole = value;
    }

    void Logger::SetLogFile(bool value)
    {
        logger->logToFile = value;
    }

    void Logger::SetLogLevel(LogLevel level)
    {
        logger->level = level;
    }

    void Logger::SetLogColor(LogType type, ConsoleColor color)
    {
        logger->colors[(size_t)type] = color;
    }

    LogLevel Logger::GetLogLevel()
    {
        return logger->level;
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
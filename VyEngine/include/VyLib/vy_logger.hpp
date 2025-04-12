#pragma once

#include <string>
#include <cstring>

#include <iostream>
#include <fstream>

#include <cstdarg>
#include <cstdlib>

#include <vector>
#include <memory>
#include <mutex>
#include <chrono>



#define VY_LOG_INFO(text, ...)    { VyLib::Log::VyLogInfo(std::string(__FUNCTION__)    + ": " + std::string(text), ## __VA_ARGS__); }
#define VY_LOG_ERROR(text, ...)   { VyLib::Log::VyLogError(std::string(__FUNCTION__)   + ": " + std::string(text), ## __VA_ARGS__); }
#define VY_LOG_WARNING(text, ...) { VyLib::Log::VyLogWarning(std::string(__FUNCTION__) + ": " + std::string(text), ## __VA_ARGS__); }

namespace VyLib
{
    enum class LogType
    {
        Info,
        Warning,
        Error
    };
    
    struct LogCmd
    {
        std::string text;
        LogType type;
        
        LogCmd(const std::string text, const LogType type)
        {
            this->text = text;
            this->type = type;
        }
    };
    
    class ILogger
    {
        public:
        virtual ~ILogger() = default;
        virtual void Log(const std::string& log, const uint32_t type) = 0;
    };
    
    
    class Log
    {
        friend class ILogger;
        public:
        
        Log() = default;
        
        static void VyLogInit();
        static void VySetLogger(ILogger* pLogger);
        static void VySetLogToFile(const bool logToFile);
        
        static void VyLog(const char* pText, const LogType type);
        static void VyLogInfo(const char* pText, ...);
        static void VyLogError(const char* pText, ...);
        static void VyLogWarning(const char* pText, ...);
        
        static void VyLog(const std::string& text, const LogType type);
        static void VyLogInfo(const std::string text, ...);
        static void VyLogError(const std::string text, ...);
        static void VyLogWarning(const std::string text, ...);
    };
}
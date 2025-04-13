#pragma once

#include <iostream>
#include <cstdarg>

#include "vy_log_settings.hpp"
#include "vy_platform.hpp"


namespace VyLib
{
    struct LoggerData;   
    
    class Logger
    {
        static LoggerData* logger;// = nullptr;
        
        static void HandleErrors(LogType type);
        static void HandleFatalErrors(LogType type);
        static const char* GetLogTypeString(LogType type);
        
        public:
        
        static void Init();
        static void Clone(LoggerData* data);
        
        static LoggerData* GetLog();
        static LogLevel GetLogLevel();
        
        
        static void LogToConsole(const char* text);
        static void LogLineToConsole(const char* text);
        static void LogToFile(const char* text);
        static void LogLineToFile(const char* text);
        
        
        static void Log(LogType type, const char* text, ...);
        static void Log(LogType type, const std::string& caller, const std::string& message);
        
        
        static void OpenLogFile(const char* filename);
        static void OpenLogFileAppend(const char* filename);
        static void CloseLogFile();
        
        
        static bool IsLogToConsole();
        static bool IsLogToFile();
        static bool IsLogFileOpened();
        static bool IsAbortOnFatal();
        static bool IsStackTraceOnError();
        
        
        static void SetLogConsole(bool value);
        static void SetLogFile(bool value);
        static void SetLogLevel(LogLevel level);
        static void SetAbortOnFatal(bool value);
        static void SetStackTraceOnError(bool value);
        static void SetLogColor(LogType type, ConsoleColor color);
        
        
        
        
        #define VYLOG_DEBUG(text, ...)   { VyLib::Logger::Log(VyLib::LogType::DEBUG,   text, __VA_ARGS__, ...); }
        #define VYLOG_INFO(text, ...)    { VyLib::Logger::Log(VyLib::LogType::INFO,    text, __VA_ARGS__, ...); }
        #define VYLOG_WARNING(text, ...) { VyLib::Logger::Log(VyLib::LogType::WARNING, text, __VA_ARGS__, ...); }
        #define VYLOG_ERROR(text, ...)   { VyLib::Logger::Log(VyLib::LogType::ERROR,   text, __VA_ARGS__, ...); }
        #define VYLOG_FATAL(text, ...)   { VyLib::Logger::Log(VyLib::LogType::FATAL,   text, __VA_ARGS__, ...); }
        
    };
    
}

// static void VyLogInfo(const char* pText, ...);
// static void VyLogError(const char* pText, ...);
// static void VyLogWarning(const char* pText, ...);

// static void VyLog(const std::string& text, const LogType type);
// static void VyLogInfo(const std::string text, ...);
// static void VyLogError(const std::string text, ...);
// static void VyLogWarning(const std::string text, ...);

// #define VY_LOG_INFO(text, ...)    { VyLib::Log::VyLogInfo(std::string(__FUNCTION__)    + ": " + std::string(text), ## __VA_ARGS__); }
// #define VY_LOG_ERROR(text, ...)   { VyLib::Log::VyLogError(std::string(__FUNCTION__)   + ": " + std::string(text), ## __VA_ARGS__); }
// #define VY_LOG_WARNING(text, ...) { VyLib::Log::VyLogWarning(std::string(__FUNCTION__) + ": " + std::string(text), ## __VA_ARGS__); }

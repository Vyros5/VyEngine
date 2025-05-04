#pragma once

#include "Support/Logger/Logger.h"

// Engine logging
#define VYTRACE(...)    VyEngine::Support::Logger::GetCoreLogger()->trace(__VA_ARGS__);
#define VYINFO(...)     VyEngine::Support::Logger::GetCoreLogger()->info(__VA_ARGS__);
#define VYWARN(...)     VyEngine::Support::Logger::GetCoreLogger()->warn(__VA_ARGS__);
#define VYERROR(...)    VyEngine::Support::Logger::GetCoreLogger()->error(__VA_ARGS__);
#define VYCRITICAL(...) VyEngine::Support::Logger::GetCoreLogger()->critical(__VA_ARGS__);

// Client logging
#define VY_CLI_TRACE(...)    VyEngine::Support::Logger::GetClientLogger()->trace(__VA_ARGS__);
#define VY_CLI_INFO(...)     VyEngine::Support::Logger::GetClientLogger()->info(__VA_ARGS__);
#define VY_CLI_WARN(...)     VyEngine::Support::Logger::GetClientLogger()->warn(__VA_ARGS__);
#define VY_CLI_ERROR(...)    VyEngine::Support::Logger::GetClientLogger()->error(__VA_ARGS__);
#define VY_CLI_CRITICAL(...) VyEngine::Support::Logger::GetClientLogger()->critical(__VA_ARGS__);
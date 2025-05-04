#pragma once

#include <string>

#define VYASSERT(condition, message) VyEngine::Support::Assertion::Assert(condition, message)

namespace VyEngine::Support
{
    /**
     *  Wrapper for C++ Assert
     */
    class Assertion
    {
    public:
        Assertion() = delete;

        static void Assert(bool condition, const std::string& message = "");
    };
}
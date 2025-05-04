#pragma once

#include <cstdint>

namespace VyEngine::GFX::Data
{
    enum class EBufferType : uint8_t
    {
        VERTEX,
        INDEX,
        UNIFORM,
        SHADER_STORAGE,
        UNKNOWN
    };


    enum class EAccessSpecifier : uint8_t
    {
        STREAM_DRAW,
        STREAM_READ,
        STREAM_COPY,
        DYNAMIC_DRAW,
        DYNAMIC_READ,
        DYNAMIC_COPY,
        STATIC_DRAW,
        STATIC_READ,
        STATIC_COPY
    };
}
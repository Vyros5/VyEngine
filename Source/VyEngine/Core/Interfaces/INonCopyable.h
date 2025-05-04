#pragma once

namespace VyEngine
{
    /**
     *  Helper class to declare a Non-Copyable and Non-Movable class.
     */
    class INonCopyable
    {
    protected:
        INonCopyable() = default;

        INonCopyable(const INonCopyable& other)            = delete;
        INonCopyable& operator=(const INonCopyable& other) = delete;

        INonCopyable(INonCopyable&& other)                 = delete;
        INonCopyable& operator=(INonCopyable&& other)      = delete;
    };

    /**
     *  Helper class to declare a Non-Copyable but Movable class.
     */
    class IMovableNonCopyable
    {
    protected:
        IMovableNonCopyable() = default;

        IMovableNonCopyable(const IMovableNonCopyable& other)            = default;
        IMovableNonCopyable& operator=(const IMovableNonCopyable& other) = default;

        IMovableNonCopyable(IMovableNonCopyable&& other)                 = delete;
        IMovableNonCopyable& operator=(IMovableNonCopyable&& other)      = delete;
    };
}
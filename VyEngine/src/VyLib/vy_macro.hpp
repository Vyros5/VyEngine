#pragma once


#include "vy_logger.hpp"

// Assert Handling
#define VY_ASSERT_ENABLED


#ifdef VY_ASSERT_ENABLED
    #define VY_ASSERT(expr, ...)                                \
    if (expr) {                                                 \
    } else {                                                    \
        VY_CRITICAL("Assertion Failed: {0}", __VA_ARGS__)       \
    }

    #define VY_CORE_ASSERT(expr, ...)                           \
    if (expr) {                                                 \
    } else {                                                    \
        VY_CORE_CRITICAL("Assertion Failed: {0}", __VA_ARGS__)  \
    }
#else
    #define VY_ASSERT(expr, ...)
    #define VY_CORE_ASSERT(expr, ...)
#endif 



namespace VyEngine
{
    template<int X, int Y>
    struct AssertEquality
    {
        static_assert(X == Y, "\nEquality check failed.\n");
        static constexpr bool value = X == Y;
    };
    
}
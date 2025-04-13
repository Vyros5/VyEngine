#pragma once

#define VYENGINE_DEBUG

// Assert Handling
#define VY_ASSERT_EXCEPTION


// VyLib::VyAssertException
#if defined(VYENGINE_DEBUG)
    #if defined(VY_ASSERT_EXCEPTION)
        #include <exception>
        namespace VyLib { class VyAssertException : public std::exception { \
            public: const char* msg; VyAssertException(const char* msg) {}  \
                    const char* what() const noexcept { return msg; } }; }
        
        #define VY_ASSERT(expr) if(!(expr)) throw VyLib::VyAssertException(#expr)
    #else
        #define VY_ASSERT(expr) assert(expr)
    #endif
#else
    #define VY_ASSERT(expr)
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
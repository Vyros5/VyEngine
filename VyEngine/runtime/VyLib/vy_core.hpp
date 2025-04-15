#pragma once 

#include <memory>

namespace VyEngine
{
    /*
     *  Unique Pointer
     *
     * 
     * 
     * 
    */
    template<typename T>
    using UniquePtr = std::unique_ptr<T>;
    
    template<typename T, typename... Args>
    constexpr UniquePtr<T> MakeUniquePtr(Args&&... args)
    {
        return std::make_unique<T>(std::forward<Args>(args)...);
    }
    

    /*
     *  Shared Pointer
     *  
     *  template <class T, class... Args>
     *  shared_ptr<T> make_shared (Args&&... args);
     * 
     *  Allocates and constructs an object of type T passing args to its constructor, 
     *  and returns an object of type shared_ptr<T> that owns and stores a pointer to 
     *  it (with a 'use count' of 1).
     * 
     *  Return Value:
     *      A shared_ptr object that owns and stores a pointer to a newly allocated object of type T.
     * 
     *  https://en.cppreference.com/w/cpp/memory/shared_ptr/make_shared
    */
    template<typename T>
    using SharedPtr = std::shared_ptr<T>;
    
    template<typename T, typename... Args>
    constexpr SharedPtr<T> MakeSharedPtr(Args&&... args)
    {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }
}
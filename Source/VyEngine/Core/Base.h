#pragma once

#include <memory>

#define BIT(x) (1 << x)

#define VY_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

template<typename T>
using Scope = std::unique_ptr<T>;

template<typename T, typename... Args>
constexpr Scope<T> MakeScope(Args&&... args)
{
    return std::make_unique<T>(std::forward<Args>(args)...);
}


template<typename T>
using Ref = std::shared_ptr<T>;

template<typename T, typename... Args>
constexpr Ref<T> MakeRef(Args&&... args)
{
    return std::make_shared<T>(std::forward<Args>(args)...);
}

/// @brief Weak Pointer
template<typename T>
using WeakRef = std::weak_ptr<T>;
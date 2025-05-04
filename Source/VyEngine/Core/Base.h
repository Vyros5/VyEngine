#pragma once

#include <memory>

#include "Support/Assert.h"
#include "Support/Logger/LogDef.h"

/// @brief Unique Pointer
template<typename T>
using Scope = std::unique_ptr<T>;

template<typename T, typename... Args>
constexpr Scope<T> MakeScope(Args&&... args)
{
    return std::make_unique<T>(std::forward<Args>(args)...);
}

/// @brief Shared Pointer
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
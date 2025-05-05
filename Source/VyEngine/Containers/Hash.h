#pragma once

// STD
#include <cstddef>
#include <type_traits>

// EA
#include <EASTL/span.h>
#include <EASTL/unordered_map.h>
#include <EASTL/utility.h>
#include <EASTL/vector.h>
#include <EASTL/weak_ptr.h>

namespace VyEngine
{
    // Golden Ratio / Fibonacci Hashing


    // Combine hash into result value.

    // 
    template<class T>
    inline void CombineHash(T& res, unsigned hash, eastl::enable_if_t<sizeof(T) == 4, int>* = 0)
    {
        res ^= hash + 0x9e3779b9 + (res << 6) + (res >> 2);
    }

    template<class T>
    inline void CombineHash(T& res, unsigned long long hash, eastl::enable_if_t<sizeof(T) == 8, int>* = 0)
    {
        res ^= hash + 0x9e3779b97f4a7c15ull + (res << 6) + (res >> 2);
    }

    // Fold 64-Bit hash into 32-Bit.
    inline unsigned FoldHash(unsigned long long value)
    {
        const auto lowValue  = static_cast<unsigned>(value);
        const auto highValue = static_cast<unsigned>(value >> 32ull); // 32ull = unsigned long long int (unsigned 64-Bit int)
    
        if (highValue == 0) { return lowValue; }

        auto res = lowValue;
        CombineHash(res, highValue);

        return res;
    }

    // Make hash for floating-point variable with zero error tolerance.
    inline unsigned MakeHash(float value)
    {
        unsigned uintVal{};
        memcpy(&uintVal, &value, sizeof(float));
        CombineHash(uintVal, 0u); // 0u - Unsigned Int 0 - Shuffle it a bit
        
        return uintVal;
    }

    // Make hash template helper.
    template <class T>
    inline unsigned MakeHash(const T& value)
    {
        const auto hash = eastl::hash<T>{}(value);
        if constexpr (sizeof(hash) > 4)
        {
            return FoldHash(hash);
        }
        else 
        {
            return hash;
        }
    }
}

namespace eastl
{

    template <class T, class Enabled> struct hash;

    namespace detail
    {
    template<typename T, typename = void> struct is_hashable : std::false_type { };
    template<typename T> struct is_hashable<T, decltype(void(&T::ToHash))> : std::true_type { };
    }
    
    template <typename T>
    struct hash<T, typename enable_if<detail::is_hashable<T>::value>::type>
    {
        size_t operator()(const T& value) const
        {
            return value.ToHash();
        }
    };

    template <class T, class U>
    struct hash<pair<T, U>>
    {
        size_t operator()(const pair<T, U>& value) const
        {
            size_t result = 0;
            VyEngine::CombineHash(result, hash<T>{}(value.first));
            VyEngine::CombineHash(result, hash<U>{}(value.second));
            return result;
        }
    };

    template <class T, class Allocator>
    struct hash<vector<T, Allocator>>
    {
        size_t operator()(const vector<T, Allocator>& value) const
        {
            size_t result = 0;
            for (const auto& elem : value)
            {
                VyEngine::CombineHash(result, hash<T>{}(elem));
            }
            return result;
        }
    };

    template <class Key, class Value, class Hash, class Predicate, class Allocator, bool bCacheHashCode>
    struct hash<unordered_map<Key, Value, Hash, Predicate, Allocator, bCacheHashCode>>
    {
        size_t operator()(const unordered_map<Key, Value, Hash, Predicate, Allocator, bCacheHashCode>& value) const
        {
            size_t result = 0;
            for (const auto& [key, elem] : value)
            {
                VyEngine::CombineHash(result, hash<Key>{}(key));
                VyEngine::CombineHash(result, hash<Value>{}(elem));
            }
            return result;
        }
    };
    
    template <class... T>
    struct hash<tuple<T...>>
    {
        size_t operator()(const tuple<T...>& value) const
        {
            size_t result = 0;
            const auto calculate = [&result](const auto&... args)
            {
                const unsigned hashes[] = {VyEngine::MakeHash(args)...};
                for (const unsigned hash : hashes)
                {
                    VyEngine::CombineHash(result, hash);
                }
            };

            eastl::apply(calculate, value);
            return result;
        }
    };
    
    template <class T>
    struct hash<span<T>>
    {
        size_t operator()(const span<T>& value) const
        {
            size_t result = 0;
            VyEngine::CombineHash(result, value.size());
            for (const auto& elem : value)
            {
                VyEngine::CombineHash(result, hash<T>{}(elem));
            }
            return result;
        }
    };
}
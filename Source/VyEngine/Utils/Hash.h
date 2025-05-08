#pragma once

#include "defines.h"



// MurmurHash2 was written by Austin Appleby, and is placed in the public
// domain. The author hereby disclaims copyright to this source code.

// Note - This code makes a few assumptions about how your machine behaves -

// 1. We can read a 4-byte value from any address without crashing
// 2. sizeof(int) == 4

// And it has a few limitations -

// 1. It will not work incrementally.
// 2. It will not produce the same results on little-endian and big-endian
//    machines.


// Platform-specific functions and macros

// Microsoft Visual Studio

#if defined(_MSC_VER)

#define BIG_CONSTANT(x) (x)

// Other compilers

#else	// defined(_MSC_VER)

#define BIG_CONSTANT(x) (x##LLU)

#endif // !defined(_MSC_VER)
//

namespace VyEngine
{
    namespace Hash
    {
        // Block read - on little-endian machines this is a single load,
        // while on big-endian or unknown machines the byte accesses should
        // still get optimized into the most efficient instruction.
        static inline u32 getblock(const u32* p)
        {
        #if defined(__BYTE_ORDER__) && (__BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__)
            return *p;
        #else
            const u8* c = (const u8*)p;
            return (u32)c[0] |
                   (u32)c[1] << 8  |
                   (u32)c[2] << 16 |
                   (u32)c[3] << 24;
        #endif
        }

        static inline u64 getblock(const u64* p)
        {
        #if defined(__BYTE_ORDER__) && (__BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__)
            return *p;
        #else
            const u8* c = (const u8*)p;
            return (u64)c[0] |
                   (u64)c[1] << 8  |
                   (u64)c[2] << 16 |
                   (u64)c[3] << 24 |
                   (u64)c[4] << 32 |
                   (u64)c[5] << 40 |
                   (u64)c[6] << 48 |
                   (u64)c[7] << 56;
        #endif
        }


        // MurmurHash2, 64-bit versions, by Austin Appleby

        // The same caveats as 32-bit MurmurHash2 apply here - beware of alignment 
        // and endian-ness issues if used across multiple platforms.

        // 64-bit hash for 64-bit platforms
        inline constexpr u64 MurmurHash64A(const void* key, i32 len, u64 seed) noexcept 
        {
            const u64 m = BIG_CONSTANT(0xc6a4a7935bd1e995);
            const i32 r = 47;

            u64 h = seed ^ (len * m);
            
            const u64* data = (const u64*)key;
            const u64* end = data + (len / 8);
        
            while (data != end) 
            {
                u64 k = getblock(data++);

                k *= m;
                k ^= k >> r;
                k *= m;

                h ^= k;
                h *= m;
            }
        
            const u8* data2 = (const u8*)data;
        
            switch (len & 7) 
            {
                case 7: h ^= (u64)(data2[6]) << 48;
                case 6: h ^= (u64)(data2[5]) << 40;
                case 5: h ^= (u64)(data2[4]) << 32;
                case 4: h ^= (u64)(data2[3]) << 24;
                case 3: h ^= (u64)(data2[2]) << 16;
                case 2: h ^= (u64)(data2[1]) << 8;
                case 1: h ^= (u64)(data2[0]);
                
                h *= m;
            };
        
            h ^= h >> r;
            h *= m;
            h ^= h >> r;
        
            return h;
        }
    }
}
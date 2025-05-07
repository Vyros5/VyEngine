#pragma once


#include <cstdint>
#include <string>

#include <glm/glm.hpp>

// ========[ TYPES ]======== //

// Unsigned Int Types

/** @brief Unsigned 8-bit integer (unsigned char) */
typedef unsigned char  u8;

/** @brief Unsigned 16-bit integer (unsigned short) */
typedef unsigned short u16;

/** @brief Unsigned 32-bit integer (unsigned int) */
typedef unsigned int u32;

/** @brief Unsigned 64-bit integer (unsigned long long) */
typedef unsigned long long u64;


// Signed Int Types

/** @brief Signed 8-bit integer (char) */
typedef signed char i8;

/** @brief Signed 16-bit integer (short) */
typedef signed short i16;

/** @brief Signed 32-bit integer (int) */
typedef signed int i32;

/** @brief Signed 64-bit integer (long long) */
typedef signed long long i64;


// Floating point Types

/** @brief 32-bit floating point number (float) */
typedef float f32;

/** @brief 64-bit floating point number (double) */
typedef double f64;


// Boolean Type

/** @brief 8-bit boolean type (bool) */
typedef bool b8;


// ===[ COMPILE-TIME ASSERTIONS ]=== //

static_assert(sizeof(bool)          == 1);
static_assert(sizeof(char)          == 1);
static_assert(sizeof(float)         == 4);
static_assert(sizeof(double)        == 8);
static_assert(sizeof(long long int) == 8);

static_assert(sizeof(i8)  == 1);
static_assert(sizeof(i16) == 2);
static_assert(sizeof(i32) == 4);
static_assert(sizeof(i64) == 8);

static_assert(sizeof(u8)  == 1);
static_assert(sizeof(u16) == 2);
static_assert(sizeof(u32) == 4);
static_assert(sizeof(u64) == 8);

static_assert(sizeof(b8)  == 1);



// String Type

/** @brief Standard Library 'string' type */
typedef std::string VyString;

/** @brief Standard Library 'string_view' type */
typedef std::string_view VyStringView;

// ================================================================================================

/// @brief Enum values for success and failure. To be used by functions as return values mostly, instead of bool.
enum VyResultEnum
{
    VY_SUCCESS,
    VY_FAILURE
};

/// @brief Default enum for returning failure or success, instead of using a bool.
struct VyResult
{
public:
    VyResult(VyResultEnum val) : m_Value(val) {}


    void operator=(VyResultEnum rhs) { m_Value = rhs; }
    bool operator==(VyResultEnum cmp) const { return m_Value == cmp; }
    bool operator!=(VyResultEnum cmp) const { return m_Value != cmp; }

    [[nodiscard]] inline bool Succeeded() const { return m_Value == VY_SUCCESS; }
    [[nodiscard]] inline bool Failed() const { return m_Value == VY_FAILURE; }

    /// @brief Used to silence compiler warnings, when success or failure doesn't matter.
    inline void Ignore()
    {
        /* dummy to be called when a return value is [[nodiscard]] but the result is not needed */
    }

    /// @brief Asserts that the function succeeded. In case of failure, the program will terminate.
    /// @param msg 
    /// @param details 
    /// @note If \a 'msg' is given, it will be the assert message. If \a 'details' is provided, \a 'msg' should contain a formatting element ({}), e.g. "Error: {}".
    void AssertSuccess(const char* msg = nullptr, const char* details = nullptr) const;

private:
    VyResultEnum m_Value;
};


/// @brief Explicit conversion to VyResult, can be overloaded for arbitrary types.
/// @param result 
/// @return VyResult
/// @note This is intentionally not done via casting operator overload (or even additional constructors) since this usually comes with a
/// considerable data loss.
inline VyResult VyToResult(VyResult result)
{
    return result;
}


typedef glm::vec2 Vec2;
typedef glm::vec3 Vec3;
typedef glm::vec4 Vec4;

typedef glm::mat2 Mat2;
typedef glm::mat3 Mat3;
typedef glm::mat4 Mat4;

typedef glm::quat Quat;
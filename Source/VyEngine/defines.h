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

static_assert(sizeof(f32)  == 4);
static_assert(sizeof(f64)  == 8);

static_assert(sizeof(b8)  == 1);

// ================================================================================================

// String Type

/** @brief Standard Library 'string' type */
typedef std::string VyString;

/** @brief Standard Library 'string_view' type */
typedef std::string_view VyStringView;

// ================================================================================================
/* Vectors / Matrices / Quaternions */

/** @brief Float (f32) Vector2(x, y) */
typedef glm::vec2 Vec2;
/** @brief Float (f32) Vector3(x, y, z) */
typedef glm::vec3 Vec3;
/** @brief Float (f32) Vector4(x, y, z, w) */
typedef glm::vec4 Vec4;

/** @brief Int (i32) Vector2(x, y) */
typedef glm::ivec2 IVec2;
/** @brief Int (i32) Vector3(x, y, z) */
typedef glm::ivec3 IVec3;
/** @brief Int (i32) Vector4(x, y, z, w) */
typedef glm::ivec4 IVec4;

/** @brief Double (f64) Vector2(x, y) */
typedef glm::dvec2 DVec2;
/** @brief Double (f64) Vector3(x, y, z) */
typedef glm::dvec3 DVec3;
/** @brief Double (f64) Vector4(x, y, z, w) */
typedef glm::dvec4 DVec4;

/** @brief Float (f32) 2 x 2 Matrix (4) */
typedef glm::mat2 Mat2;
/** @brief Float (f32) 3 x 3 Matrix (9) */
typedef glm::mat3 Mat3;
/** @brief Float (f32) 4 x 4 Matrix (16) */
typedef glm::mat4 Mat4;

/** @brief Float (f32) Quaternion (4 x 4) */
typedef glm::quat Quat;

// ================================================================================================
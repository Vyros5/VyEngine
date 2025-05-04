#pragma once


#include <glad/glad.h>

#include "Graphics/Data/EData.h"

#include "Graphics/Data/EBuffer.h"
#include "Graphics/Data/EPixel.h"
#include "Graphics/Data/EShader.h"
#include "Graphics/Data/ERender.h"

#include "Utils/EnumMapper.hpp"

namespace VyEngine::GFX::API
{
	template <typename ValueType, typename EnumType>
	constexpr ValueType EnumToValue(EnumType enumValue)
	{
		return VyEngine::Utils::ToValueImpl<EnumType, ValueType>(enumValue);
	}

	template <typename EnumType, typename ValueType>
	constexpr EnumType ValueToEnum(ValueType value)
	{
		return VyEngine::Utils::FromValueImpl<EnumType, ValueType>(value);
	}
}

// ================================================================================================

template <>
struct VyEngine::Utils::MappingFor<VyEngine::GFX::Data::EComparaisonAlgorithm, GLenum>
{
	using EnumType = VyEngine::GFX::Data::EComparaisonAlgorithm;
	using type = std::tuple<
		EnumValuePair<EnumType::NEVER, GL_NEVER>,
		EnumValuePair<EnumType::LESS, GL_LESS>,
		EnumValuePair<EnumType::EQUAL, GL_EQUAL>,
		EnumValuePair<EnumType::LESS_EQUAL, GL_LEQUAL>,
		EnumValuePair<EnumType::GREATER, GL_GREATER>,
		EnumValuePair<EnumType::NOTEQUAL, GL_NOTEQUAL>,
		EnumValuePair<EnumType::GREATER_EQUAL, GL_GEQUAL>,
		EnumValuePair<EnumType::ALWAYS, GL_ALWAYS>
	>;
};

template <>
struct VyEngine::Utils::MappingFor<VyEngine::GFX::Data::ERasterizationMode, GLenum>
{
	using EnumType = VyEngine::GFX::Data::ERasterizationMode;
	using type = std::tuple<
		EnumValuePair<EnumType::POINT, GL_POINT>,
		EnumValuePair<EnumType::LINE, GL_LINE>,
		EnumValuePair<EnumType::FILL, GL_FILL>
	>;
};

template <>
struct VyEngine::Utils::MappingFor<VyEngine::GFX::Data::ECullFace, GLenum>
{
	using EnumType = VyEngine::GFX::Data::ECullFace;
	using type = std::tuple<
		EnumValuePair<EnumType::FRONT, GL_FRONT>,
		EnumValuePair<EnumType::BACK, GL_BACK>,
		EnumValuePair<EnumType::FRONT_AND_BACK, GL_FRONT_AND_BACK>
	>;
};

template <>
struct VyEngine::Utils::MappingFor<VyEngine::GFX::Data::EOperation, GLenum>
{
	using EnumType = VyEngine::GFX::Data::EOperation;
	using type = std::tuple<
		EnumValuePair<EnumType::KEEP, GL_KEEP>,
		EnumValuePair<EnumType::ZERO, GL_ZERO>,
		EnumValuePair<EnumType::REPLACE, GL_REPLACE>,
		EnumValuePair<EnumType::INCREMENT, GL_INCR>,
		EnumValuePair<EnumType::INCREMENT_WRAP, GL_INCR_WRAP>,
		EnumValuePair<EnumType::DECREMENT, GL_DECR>,
		EnumValuePair<EnumType::DECREMENT_WRAP, GL_DECR_WRAP>,
		EnumValuePair<EnumType::INVERT, GL_INVERT>
	>;
};

template <>
struct VyEngine::Utils::MappingFor<VyEngine::GFX::Data::ERenderingCapability, GLenum>
{
	using EnumType = VyEngine::GFX::Data::ERenderingCapability;
	using type = std::tuple<
		EnumValuePair<EnumType::BLEND, GL_BLEND>,
		EnumValuePair<EnumType::CULL_FACE, GL_CULL_FACE>,
		EnumValuePair<EnumType::DEPTH_TEST, GL_DEPTH_TEST>,
		EnumValuePair<EnumType::DITHER, GL_DITHER>,
		EnumValuePair<EnumType::POLYGON_OFFSET_FILL, GL_POLYGON_OFFSET_FILL>,
		EnumValuePair<EnumType::SAMPLE_ALPHA_TO_COVERAGE, GL_SAMPLE_ALPHA_TO_COVERAGE>,
		EnumValuePair<EnumType::SAMPLE_COVERAGE, GL_SAMPLE_COVERAGE>,
		EnumValuePair<EnumType::SCISSOR_TEST, GL_SCISSOR_TEST>,
		EnumValuePair<EnumType::STENCIL_TEST, GL_STENCIL_TEST>,
		EnumValuePair<EnumType::MULTISAMPLE, GL_MULTISAMPLE>
	>;
};

template <>
struct VyEngine::Utils::MappingFor<VyEngine::GFX::Data::EPrimitiveMode, GLenum>
{
	using EnumType = VyEngine::GFX::Data::EPrimitiveMode;
	using type = std::tuple<
		EnumValuePair<EnumType::POINTS, GL_POINTS>,
		EnumValuePair<EnumType::LINES, GL_LINES>,
		EnumValuePair<EnumType::LINE_LOOP, GL_LINE_LOOP>,
		EnumValuePair<EnumType::LINE_STRIP, GL_LINE_STRIP>,
		EnumValuePair<EnumType::TRIANGLES, GL_TRIANGLES>,
		EnumValuePair<EnumType::TRIANGLE_STRIP, GL_TRIANGLE_STRIP>,
		EnumValuePair<EnumType::TRIANGLE_FAN, GL_TRIANGLE_FAN>,
		EnumValuePair<EnumType::LINES_ADJACENCY, GL_LINES_ADJACENCY>,
		EnumValuePair<EnumType::LINE_STRIP_ADJACENCY, GL_LINE_STRIP_ADJACENCY>,
		EnumValuePair<EnumType::PATCHES, GL_PATCHES>
	>;
};

// template <>
// struct VyEngine::Utils::MappingFor<VyEngine::GFX::Data::EFormat, GLenum>
// {
// 	using EnumType = VyEngine::GFX::Data::EFormat;
// 	using type = std::tuple<
// 		EnumValuePair<EnumType::RED, GL_RED>,
// 		EnumValuePair<EnumType::RG, GL_RG>,
// 		EnumValuePair<EnumType::RGB, GL_RGB>,
// 		EnumValuePair<EnumType::BGR, GL_BGR>,
// 		EnumValuePair<EnumType::RGBA, GL_RGBA>,
// 		EnumValuePair<EnumType::BGRA, GL_BGRA>,
// 		EnumValuePair<EnumType::RED_INTEGER, GL_RED_INTEGER>,
// 		EnumValuePair<EnumType::RG_INTEGER, GL_RG_INTEGER>,
// 		EnumValuePair<EnumType::RGB_INTEGER, GL_RGB_INTEGER>,
// 		EnumValuePair<EnumType::BGR_INTEGER, GL_BGR_INTEGER>,
// 		EnumValuePair<EnumType::RGBA_INTEGER, GL_RGBA_INTEGER>,
// 		EnumValuePair<EnumType::BGRA_INTEGER, GL_BGRA_INTEGER>,
// 		EnumValuePair<EnumType::STENCIL_INDEX, GL_STENCIL_INDEX>,
// 		EnumValuePair<EnumType::DEPTH_COMPONENT, GL_DEPTH_COMPONENT>,
// 		EnumValuePair<EnumType::DEPTH_STENCIL, GL_DEPTH_STENCIL>
// 	>;
// };

// template <>
// struct VyEngine::Utils::MappingFor<VyEngine::GFX::Data::ETextureFilteringMode, GLenum>
// {
// 	using EnumType = VyEngine::GFX::Data::ETextureFilteringMode;
// 	using type = std::tuple<
// 		EnumValuePair<EnumType::NEAREST, GL_NEAREST>,
// 		EnumValuePair<EnumType::LINEAR, GL_LINEAR>,
// 		EnumValuePair<EnumType::NEAREST_MIPMAP_NEAREST, GL_NEAREST_MIPMAP_NEAREST>,
// 		EnumValuePair<EnumType::LINEAR_MIPMAP_LINEAR, GL_LINEAR_MIPMAP_LINEAR>,
// 		EnumValuePair<EnumType::LINEAR_MIPMAP_NEAREST, GL_LINEAR_MIPMAP_NEAREST>,
// 		EnumValuePair<EnumType::NEAREST_MIPMAP_LINEAR, GL_NEAREST_MIPMAP_LINEAR>
// 	>;
// };

// template <>
// struct VyEngine::Utils::MappingFor<VyEngine::GFX::Data::ETextureWrapMode, GLenum>
// {
// 	using EnumType = VyEngine::GFX::Data::ETextureWrapMode;
// 	using type = std::tuple<
// 		EnumValuePair<EnumType::REPEAT, GL_REPEAT>,
// 		EnumValuePair<EnumType::CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE>,
// 		EnumValuePair<EnumType::CLAMP_TO_BORDER, GL_CLAMP_TO_BORDER>,
// 		EnumValuePair<EnumType::MIRRORED_REPEAT, GL_MIRRORED_REPEAT>,
// 		EnumValuePair<EnumType::MIRROR_CLAMP_TO_EDGE, GL_MIRROR_CLAMP_TO_EDGE>
// 	>;
// };

template <>
struct VyEngine::Utils::MappingFor<VyEngine::GFX::Data::EPixelDataFormat, GLenum>
{
	using EnumType = VyEngine::GFX::Data::EPixelDataFormat;
	using type = std::tuple<
		EnumValuePair<EnumType::STENCIL_INDEX, GL_STENCIL_INDEX>,
		EnumValuePair<EnumType::DEPTH_COMPONENT, GL_DEPTH_COMPONENT>,
		EnumValuePair<EnumType::RED, GL_RED>,
		EnumValuePair<EnumType::GREEN, GL_GREEN>,
		EnumValuePair<EnumType::BLUE, GL_BLUE>,
		EnumValuePair<EnumType::ALPHA, GL_ALPHA>,
		EnumValuePair<EnumType::RGB, GL_RGB>,
		EnumValuePair<EnumType::BGR, GL_BGR>,
		EnumValuePair<EnumType::RGBA, GL_RGBA>,
		EnumValuePair<EnumType::BGRA, GL_BGRA>
	>;
};

template <>
struct VyEngine::Utils::MappingFor<VyEngine::GFX::Data::EPixelDataType, GLenum>
{
	using EnumType = VyEngine::GFX::Data::EPixelDataType;
	using type = std::tuple<
		EnumValuePair<EnumType::BYTE, GL_BYTE>,
		EnumValuePair<EnumType::UNSIGNED_BYTE, GL_UNSIGNED_BYTE>,
		EnumValuePair<EnumType::SHORT, GL_SHORT>,
		EnumValuePair<EnumType::UNSIGNED_SHORT, GL_UNSIGNED_SHORT>,
		EnumValuePair<EnumType::INT, GL_INT>,
		EnumValuePair<EnumType::UNSIGNED_INT, GL_UNSIGNED_INT>,
		EnumValuePair<EnumType::FLOAT, GL_FLOAT>,
		EnumValuePair<EnumType::UNSIGNED_BYTE_3_3_2, GL_UNSIGNED_BYTE_3_3_2>,
		EnumValuePair<EnumType::UNSIGNED_BYTE_2_3_3_REV, GL_UNSIGNED_BYTE_2_3_3_REV>,
		EnumValuePair<EnumType::UNSIGNED_SHORT_5_6_5, GL_UNSIGNED_SHORT_5_6_5>,
		EnumValuePair<EnumType::UNSIGNED_SHORT_5_6_5_REV, GL_UNSIGNED_SHORT_5_6_5_REV>,
		EnumValuePair<EnumType::UNSIGNED_SHORT_4_4_4_4, GL_UNSIGNED_SHORT_4_4_4_4>,
		EnumValuePair<EnumType::UNSIGNED_SHORT_4_4_4_4_REV, GL_UNSIGNED_SHORT_4_4_4_4_REV>,
		EnumValuePair<EnumType::UNSIGNED_SHORT_5_5_5_1, GL_UNSIGNED_SHORT_5_5_5_1>,
		EnumValuePair<EnumType::UNSIGNED_SHORT_1_5_5_5_REV, GL_UNSIGNED_SHORT_1_5_5_5_REV>,
		EnumValuePair<EnumType::UNSIGNED_INT_8_8_8_8, GL_UNSIGNED_INT_8_8_8_8>,
		EnumValuePair<EnumType::UNSIGNED_INT_8_8_8_8_REV, GL_UNSIGNED_INT_8_8_8_8_REV>,
		EnumValuePair<EnumType::UNSIGNED_INT_10_10_10_2, GL_UNSIGNED_INT_10_10_10_2>,
		EnumValuePair<EnumType::UNSIGNED_INT_2_10_10_10_REV, GL_UNSIGNED_INT_2_10_10_10_REV>
	>;
};

template<>
struct VyEngine::Utils::MappingFor<VyEngine::GFX::Data::EBufferType, GLenum>
{
    using EnumType = VyEngine::GFX::Data::EBufferType;
    using type = std::tuple<
        EnumValuePair<EnumType::VERTEX,         GL_ARRAY_BUFFER>,
        EnumValuePair<EnumType::INDEX,          GL_ELEMENT_ARRAY_BUFFER>,
        EnumValuePair<EnumType::UNIFORM,        GL_UNIFORM_BUFFER>,
        EnumValuePair<EnumType::SHADER_STORAGE, GL_SHADER_STORAGE_BUFFER>
    >;
};


template<>
struct VyEngine::Utils::MappingFor<VyEngine::GFX::Data::EShaderType, GLenum>
{
    using EnumType = VyEngine::GFX::Data::EShaderType;
    using type = std::tuple<
        EnumValuePair<EnumType::VERTEX,   GL_VERTEX_SHADER>,
        EnumValuePair<EnumType::FRAGMENT, GL_FRAGMENT_SHADER>
    >;
};


template<>
struct VyEngine::Utils::MappingFor<VyEngine::GFX::Data::EUniformType, GLenum>
{
    using EnumType = VyEngine::GFX::Data::EUniformType;
    using type = std::tuple<
        EnumValuePair<EnumType::BOOL,         GL_BOOL>,
        EnumValuePair<EnumType::INT,          GL_INT>,
        EnumValuePair<EnumType::FLOAT,        GL_FLOAT>,
        EnumValuePair<EnumType::FLOAT_VEC2,   GL_FLOAT_VEC2>,
        EnumValuePair<EnumType::FLOAT_VEC3,   GL_FLOAT_VEC3>,
        EnumValuePair<EnumType::FLOAT_VEC4,   GL_FLOAT_VEC4>,
        EnumValuePair<EnumType::FLOAT_MAT4,   GL_FLOAT_MAT4>,
        EnumValuePair<EnumType::DOUBLE_MAT4,  GL_DOUBLE_MAT4>,
        EnumValuePair<EnumType::SAMPLER_2D,   GL_SAMPLER_2D>,
        EnumValuePair<EnumType::SAMPLER_CUBE, GL_SAMPLER_CUBE>
    >;
};


template<>
struct VyEngine::Utils::MappingFor<VyEngine::GFX::Data::EAccessSpecifier, GLenum>
{
    using EnumType = VyEngine::GFX::Data::EAccessSpecifier;
    using type = std::tuple<
        EnumValuePair<EnumType::STREAM_DRAW,  GL_STREAM_DRAW>,
        EnumValuePair<EnumType::STREAM_READ,  GL_STREAM_READ>,
        EnumValuePair<EnumType::STREAM_COPY,  GL_STREAM_COPY>,
        EnumValuePair<EnumType::DYNAMIC_DRAW, GL_DYNAMIC_DRAW>,
        EnumValuePair<EnumType::DYNAMIC_READ, GL_DYNAMIC_READ>,
        EnumValuePair<EnumType::DYNAMIC_COPY, GL_DYNAMIC_COPY>,
        EnumValuePair<EnumType::STATIC_DRAW,  GL_STATIC_DRAW>,
        EnumValuePair<EnumType::STATIC_READ,  GL_STATIC_READ>,
        EnumValuePair<EnumType::STATIC_COPY,  GL_STATIC_COPY>
    >;
};


template<>
struct VyEngine::Utils::MappingFor<VyEngine::GFX::Data::EDataType, GLenum>
{
    using EnumType = VyEngine::GFX::Data::EDataType;
    using type = std::tuple<
        EnumValuePair<EnumType::BYTE,           GL_BYTE>,
        EnumValuePair<EnumType::UNSIGNED_BYTE,  GL_UNSIGNED_BYTE>,
        EnumValuePair<EnumType::SHORT,          GL_SHORT>,
        EnumValuePair<EnumType::UNSIGNED_SHORT, GL_UNSIGNED_SHORT>,
        EnumValuePair<EnumType::INT,            GL_INT>,
        EnumValuePair<EnumType::UNSIGNED_INT,   GL_UNSIGNED_INT>,
        EnumValuePair<EnumType::FLOAT,          GL_FLOAT>,
        EnumValuePair<EnumType::DOUBLE,         GL_DOUBLE>
    >;
};


// template<>
// struct VyEngine::Utils::MappingFor<VyEngine::GFX::Data::EPixelDataType, GLenum>
// {
//     using EnumType = VyEngine::GFX::Data::EPixelDataType;
//     using type = std::tuple<
//         EnumValuePair<EnumType::BYTE,                        GL_BYTE>,
//         EnumValuePair<EnumType::UNSIGNED_BYTE,               GL_UNSIGNED_BYTE>,
//         EnumValuePair<EnumType::SHORT,                       GL_SHORT>,
//         EnumValuePair<EnumType::UNSIGNED_SHORT,              GL_UNSIGNED_SHORT>,
//         EnumValuePair<EnumType::INT,                         GL_INT>,
//         EnumValuePair<EnumType::UNSIGNED_INT,                GL_UNSIGNED_INT>,
//         EnumValuePair<EnumType::FLOAT,                       GL_FLOAT>,
//         EnumValuePair<EnumType::UNSIGNED_BYTE_3_3_2,         GL_UNSIGNED_BYTE_3_3_2>,
//         EnumValuePair<EnumType::UNSIGNED_BYTE_2_3_3_REV,     GL_UNSIGNED_BYTE_2_3_3_REV>,
//         EnumValuePair<EnumType::UNSIGNED_SHORT_5_6_5,        GL_UNSIGNED_SHORT_5_6_5>,
//         EnumValuePair<EnumType::UNSIGNED_SHORT_5_6_5_REV,    GL_UNSIGNED_SHORT_5_6_5_REV>,
//         EnumValuePair<EnumType::UNSIGNED_SHORT_4_4_4_4,      GL_UNSIGNED_SHORT_4_4_4_4>,
//         EnumValuePair<EnumType::UNSIGNED_SHORT_4_4_4_4_REV,  GL_UNSIGNED_SHORT_4_4_4_4_REV>,
//         EnumValuePair<EnumType::UNSIGNED_SHORT_5_5_5_1,      GL_UNSIGNED_SHORT_5_5_5_1>,
//         EnumValuePair<EnumType::UNSIGNED_SHORT_1_5_5_5_REV,  GL_UNSIGNED_SHORT_1_5_5_5_REV>,
//         EnumValuePair<EnumType::UNSIGNED_INT_8_8_8_8,        GL_UNSIGNED_INT_8_8_8_8>,
//         EnumValuePair<EnumType::UNSIGNED_INT_8_8_8_8_REV,    GL_UNSIGNED_INT_8_8_8_8_REV>,
//         EnumValuePair<EnumType::UNSIGNED_INT_10_10_10_2,     GL_UNSIGNED_INT_10_10_10_2>,
//         EnumValuePair<EnumType::UNSIGNED_INT_2_10_10_10_REV, GL_UNSIGNED_INT_2_10_10_10_REV>
//     >;
// };


// template<>
// struct VyEngine::Utils::MappingFor<VyEngine::GFX::Data::EPixelDataFormat, GLenum>
// {
//     using EnumType = VyEngine::GFX::Data::EPixelDataFormat;
//     using type = std::tuple<
//         EnumValuePair<EnumType::STENCIL_INDEX, GL_STENCIL_INDEX>,
//         EnumValuePair<EnumType::DEPTH_COMPONENT, GL_DEPTH_COMPONENT>,
//         EnumValuePair<EnumType::RED, GL_RED>,
//         EnumValuePair<EnumType::GREEN, GL_GREEN>,
//         EnumValuePair<EnumType::BLUE, GL_BLUE>,
//         EnumValuePair<EnumType::ALPHA, GL_ALPHA>,
//         EnumValuePair<EnumType::RGB, GL_RGB>,
//         EnumValuePair<EnumType::BGR, GL_BGR>,
//         EnumValuePair<EnumType::RGBA, GL_RGBA>,
//         EnumValuePair<EnumType::BGRA, GL_BGRA>
//     >;
// };

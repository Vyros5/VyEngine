#pragma once

#include <cstdint>

namespace VyEngine::GFX::Data
{
	enum class EGraphicsBackend : uint8_t
	{
		NONE,
		OPENGL
	};


    enum class ERenderingCapability : uint8_t
    {
		BLEND,                      // Blend the computed fragment color values with the values in the color buffers. See glBlendFunc.
		CULL_FACE,                  // Cull polygons based on their winding in window coordinates.
		DEPTH_TEST,                 // Do depth comparisons and update the depth buffer. Note that even if the depth buffer exists and the depth mask is non-zero, the depth buffer is not updated if the depth test is disabled.
		DITHER,                     // Dither color components or indices before they are written to the color buffer.
		POLYGON_OFFSET_FILL,        // An offset is added to depth values of a polygon's fragments produced by rasterization.
		SAMPLE_ALPHA_TO_COVERAGE,   // Compute a temporary coverage value where each bit is determined by the alpha value at the corresponding sample location. The temporary coverage value is then ANDed with the fragment coverage value.
		SAMPLE_COVERAGE,            // The fragment's coverage is ANDed with the temporary coverage value. If GL_SAMPLE_COVERAGE_INVERT is set to GL_TRUE, invert the coverage value.
		SCISSOR_TEST,               // Discard fragments that are outside the scissor rectangle.
		STENCIL_TEST,               // Do stencil testing and update the stencil buffer.
		MULTISAMPLE                 // Use multiple fragment samples in computing the final color of a pixel.	
    };


	enum class ERasterizationMode : uint8_t
	{
		POINT,	// Polygon vertices that are marked as the start of a boundary edge are drawn as points. Point attributes such as GL_POINT_SIZE and GL_POINT_SMOOTH control the rasterization of the points. Polygon rasterization attributes other than GL_POLYGON_MODE have no effect.
		LINE,	// Boundary edges of the polygon are drawn as line segments. Line attributes such as GL_LINE_WIDTH and GL_LINE_SMOOTH control the rasterization of the lines. Polygon rasterization attributes other than GL_POLYGON_MODE have no effect.
		FILL	// The interior of the polygon is filled. Polygon attributes such as GL_POLYGON_SMOOTH control the rasterization of the polygon.
	};


	enum class EComparaisonAlgorithm : uint8_t
	{
		NEVER,
		LESS,
		EQUAL,
		LESS_EQUAL,
		GREATER,
		NOTEQUAL,
		GREATER_EQUAL,
		ALWAYS
	};


	enum class EOperation : uint8_t
	{
		ZERO,
		KEEP,
		REPLACE,
		INCREMENT,
		INCREMENT_WRAP,
		DECREMENT,
		DECREMENT_WRAP,
		INVERT
	};


	enum class ECullFace : uint8_t
	{
		FRONT,
		BACK,
		FRONT_AND_BACK
	};
}
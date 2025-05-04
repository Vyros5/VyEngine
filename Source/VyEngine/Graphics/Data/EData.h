#pragma once

#include <cstdint>

namespace VyEngine::GFX::Data
{
	enum class EDataType : uint8_t
	{
		BYTE,
		UNSIGNED_BYTE,
		SHORT,
		UNSIGNED_SHORT,
		INT,
		UNSIGNED_INT,
		FLOAT,
		DOUBLE
	};
}
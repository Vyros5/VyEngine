#pragma once

#include <string>

namespace VyEngine::GFX::Data
{
    struct ShaderCompilationResult
	{
		bool success;
		std::string message;
	};

	struct ShaderLinkingResult
	{
		const bool success;
		const std::string message;
	};
}
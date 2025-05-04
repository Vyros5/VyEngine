#pragma once

namespace VyEngine::Window::Data
{

    enum class ECursorMode
    {
		NORMAL		= 0x00034001,
		HIDDEN		= 0x00034002,
		DISABLED	= 0x00034003
    };


    enum class ECursorType
    {
		ARROW		= 0x00036001,
		IBEAM		= 0x00036002,
		CROSSHAIR	= 0x00036003,
		HAND		= 0x00036004,
		HRESIZE		= 0x00036005,
		VRESIZE		= 0x00036006
    };
}
#ifndef _FOSL_ILI9341_ROTATIONS_H_
#define _FOSL_ILI9341_ROTATIONS_H_

namespace fosl
{
	namespace Ili9341
	{
		enum class ROTATION : uint8_t
		{
			PORTRAIT,
			LANDSCAPE,
			REVERSE_PORTRAIT,
			REVERSE_LANDSCAPE,
		};
	}
}

#endif

#ifndef _FOSL_ILI9341_ROTATION_HPP_
#define _FOSL_ILI9341_ROTATION_HPP_

namespace FOSL
{
	namespace ILI9341
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

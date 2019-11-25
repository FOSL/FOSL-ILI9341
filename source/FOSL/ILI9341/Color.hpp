#ifndef _FOSL_ILI9341_COLOR_HPP_
#define _FOSL_ILI9341_COLOR_HPP_

namespace FOSL
{
	namespace ILI9341
	{
		// TODO: Make more generic

		struct Color
		{
			unsigned int b : 5;
			unsigned int g : 6;
			unsigned int r : 5;

			operator uint16_t() { return *((uint16_t*) this); }
		};
	}
}

#endif

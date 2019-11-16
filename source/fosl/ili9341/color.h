#ifndef _FOSL_ILI9341_COLOR_H_
#define _FOSL_ILI9341_COLOR_H_

namespace fosl
{
	namespace Ili9341
	{
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

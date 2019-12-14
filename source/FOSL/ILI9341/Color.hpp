#ifndef _FOSL_ILI9341_COLOR_HPP_
#define _FOSL_ILI9341_COLOR_HPP_

namespace FOSL
{
	namespace ILI9341
	{
		namespace Color
		{
			struct RGB565
			{
				unsigned int r : 5;
				unsigned int g : 6;
				unsigned int b : 5;

				inline operator uint16_t(void) { return *((uint16_t*) this); }
			};

			struct BGR565
			{
				unsigned int b : 5;
				unsigned int g : 6;
				unsigned int r : 5;

				inline operator uint16_t(void) { return *((uint16_t*) this); }
			};
		}
	}
}

#endif

#ifndef _FOSL_ILI9341_COMMAND_HPP_
#define _FOSL_ILI9341_COMMAND_HPP_

namespace FOSL
{
	namespace ILI9341
	{
		enum class COMMAND : uint8_t
		{
			RESET             = 0x01,
			SLEEP_IN          = 0x10,
			SLEEP_OUT         = 0x11,
			GAMMA             = 0x26,
			DISPLAY_OFF       = 0x28,
			DISPLAY_ON        = 0x29,
			COLUMN_ADDR       = 0x2A,
			PAGE_ADDR         = 0x2B,
			GRAM              = 0x2C,
			TEARING_OFF       = 0x34,
			TEARING_ON        = 0x35,
			DISPLAY_INVERSION = 0xb4,
			MAC               = 0x36,
			PIXEL_FORMAT      = 0x3A,
			WDB               = 0x51,
			WCD               = 0x53,
			RGB_INTERFACE     = 0xB0,
			FRC               = 0xB1,
			BPC               = 0xB5,
			DFC               = 0xB6,
			ENTRY_MODE_SET    = 0xB7,
			POWER1            = 0xC0,
			POWER2            = 0xC1,
			VCOM1             = 0xC5,
			VCOM2             = 0xC7,
			POWERA            = 0xCB,
			POWERB            = 0xCF,
			PGAMMA            = 0xE0,
			NGAMMA            = 0xE1,
			DTCA              = 0xE8,
			DTCB              = 0xEA,
			POWER_SEQ         = 0xED,
			// 3GAMMA_EN         = 0xF2,
			INTERFACE         = 0xF6,
			PRC               = 0xF7,
			VERTICAL_SCROLL   = 0x33,
			MADCTL_MY         = 0x80,
			MADCTL_MX         = 0x40,
			MADCTL_MV         = 0x20,
			MADCTL_ML         = 0x10,
			MADCTL_RGB        = 0x00,
			MADCTL_BGR        = 0x08,
			MADCTL_MH         = 0x04,
		};
	}
}

#endif

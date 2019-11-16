#ifndef _FOSL_ILI9341_BASE_H_
#define _FOSL_ILI9341_BASE_H_

#include <fosl/util.h>

#include "fosl/ili9341/defs.h"
#include "fosl/ili9341/color.h"
#include "fosl/ili9341/point.h"

namespace fosl
{
	namespace Ili9341
	{
		class Base
		{
			public: // CONSTRUCTORS
				Base(uint16_t width, uint16_t height);
			public: // DESTRUCTOR
				~Base(void) = default;

			public: // SETTERS
				void set_rotation(ROTATION new_rotation);
				void set_window_location(const Point& point0, const Point& point1);

			public: // METHODS
				void initialize(void);
				//
				virtual void send(COMMAND command) = 0;
				virtual void send(Color color) = 0;
				virtual void send(uint8_t data) = 0;
				virtual void delay_ms(uint8_t ms) = 0;
				//
				void pixel(const Point& point, Color color);
				void fill(Color color);
				void rectangle(const Point& point0, const Point& point1, Color color, bool fill = false);
				// void circle(int16_t x0, int16_t y0, int16_t r, Color color, bool fill = false);
				// void line(const Point& point0, const Point& point1, Color color);
				// void line_horizontal(const Point& starting_point, int16_t w, Color color);
				// void line_vertical  (const Point& starting_point, int16_t h, Color color);
				// void triangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, Color color, fill = false);
				// void putc(int16_t x, int16_t y, char  c,    Color foreground_color, Color background_color, uint8_t size);
				// void puts(int16_t x, int16_t y, char* text, Color foreground_color, Color background_color, uint8_t size);
				void image(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint8_t* data);

			private:
				ROTATION rotation;
				const uint16_t width;
				const uint16_t height;

			private:
				// void drawCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername, Color color);
				// void fillCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername, int16_t delta, Color color);
		};
	}
}

#endif

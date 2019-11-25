#ifndef _FOSL_ILI9341_BASE_HPP_
#define _FOSL_ILI9341_BASE_HPP_

#include <FOSL/Utilities.hpp>

#include "FOSL/ILI9341/COMMAND.hpp"
#include "FOSL/ILI9341/ROTATION.hpp"
#include "FOSL/ILI9341/Point.hpp"
#include "FOSL/ILI9341/Color.hpp"

namespace FOSL
{
	namespace ILI9341
	{
		using Point = Math::Vector2<uint16_t>;
		using Size  = Math::Vector2<uint16_t>;

		class Base
		{
			public: // CONSTRUCTORS
				Base(uint16_t width, uint16_t height);
			public: // DESTRUCTOR
				~Base(void) = default;

			private: // VARIABLES
				ROTATION rotation;
				const uint16_t WIDTH;
				const uint16_t HEIGHT;

			public: // SETTERS
				void set_window_location(Point point, Size size);
				void set(ROTATION rotation);

			public: // METHODS
				void initialize(void);

				virtual void send(COMMAND command) = 0;
				virtual void send(Color color) = 0;
				virtual void send(uint8_t data) = 0;

				virtual void delay_ms(uint8_t ms) = 0;

				void fill(Color color);
				void draw_pixel(Point point, Color color);
				void draw_full_rectangle(Point point, Size size, Color color);
				// void rectangle_outline(const Point& point0, const Point& point1, Color color);
				void draw_buffer(Point point, Size size, const Color* data);
				// void circle(int16_t x0, int16_t y0, int16_t r, Color color, bool fill = false);
				// void line(const Point& point0, const Point& point1, Color color);
				// void line_horizontal(const Point& starting_point, int16_t w, Color color);
				// void line_vertical  (const Point& starting_point, int16_t h, Color color);
				// void triangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, Color color, fill = false);
				// void putc(int16_t x, int16_t y, char  c,    Color foreground_color, Color background_color, uint8_t size);
				// void puts(int16_t x, int16_t y, char* text, Color foreground_color, Color background_color, uint8_t size);
				// void drawCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername, Color color);
				// void fillCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername, int16_t delta, Color color);
		};
	}
}

#endif

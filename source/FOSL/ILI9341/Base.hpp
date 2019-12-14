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

		template <typename TColor>
		class Base
		{
			public: // CONSTRUCTORS
				Base(void) = default;
			public: // DESTRUCTOR
				virtual ~Base(void) = default;

			private: // VARIABLES
				ROTATION rotation;

			public: // GETTERS
				uint16_t get_width (void) const;
				uint16_t get_height(void) const;
			public: // SETTERS
				void set_window_location(Point point, Size size);
				void set(ROTATION rotation);

			public: // METHODS
				void initialize(void);

				virtual void send(COMMAND command) = 0;
				virtual void send(TColor color) = 0;
				virtual void send(uint8_t data) = 0;

				virtual void delay_ms(uint8_t ms) = 0;

				// void fill(TColor color);
				void draw_pixel(Point point, TColor color);
				void draw_full_rectangle(Point point, Size size, TColor color);
				void draw_buffer(Point point, Size size, const TColor* data);
		};

		#include "FOSL/ILI9341/Base-impl.hpp"
	}
}

#endif

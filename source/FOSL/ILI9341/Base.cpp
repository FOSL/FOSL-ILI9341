#include "FOSL/ILI9341/Base.hpp"

namespace FOSL
{
	namespace ILI9341
	{
		// CONSTRUCTORS
		Base::Base(uint16_t width, uint16_t height)
			: WIDTH(width), HEIGHT(height)
		{
		}

		// SETTERS
		void Base::set_window_location(Point point, Size size)
		{
			send(COMMAND::COLUMN_ADDR);
			send(((point.x         ) >> 8) & 0xFF);
			send(((point.x         ) >> 0) & 0xFF);
			send(((point.x + size.x) >> 8) & 0xFF);
			send(((point.x + size.x) >> 0) & 0xFF);

			send(COMMAND::PAGE_ADDR);
			send(((point.y         ) >> 8) & 0xFF);
			send(((point.y         ) >> 0) & 0xFF);
			send(((point.y + size.y) >> 8) & 0xFF);
			send(((point.y + size.y) >> 0) & 0xFF);

			send(COMMAND::GRAM);
		}
		void Base::set(ROTATION rotation)
		{
			static const uint8_t MY  = 0b10000000;
			static const uint8_t MX  = 0b01000000;
			static const uint8_t MV  = 0b00100000;
			static const uint8_t BGR = 0b00001000;

			rotation = rotation;

			send(COMMAND::MAC);
			switch(rotation)
			{
				case ROTATION::PORTRAIT:
					send(MY | BGR);
					break;
				case ROTATION::LANDSCAPE:
					send(MV | BGR);
					break;
				case ROTATION::REVERSE_PORTRAIT:
					send(MX | BGR);
					break;
				case ROTATION::REVERSE_LANDSCAPE:
					send(MX | MY | MV | BGR);
					break;
			}
		}

		// METHODS
		void Base::initialize(void)
		{
			send(COMMAND::RESET);
			delay_ms(200);
			send(COMMAND::SLEEP_OUT);
			delay_ms(200);
			send(COMMAND::DISPLAY_ON);
			delay_ms(200);

			// POWER CONTROL
			send(COMMAND::POWER1);
			send(0x26); // GVDD = 4.75v
			send(COMMAND::POWER2);
			send(0x11); // AVDD=VCIx2, VGH=VCIx7, VGL=-VCIx3

			// VCOM
			send(COMMAND::VCOM1);
			send(0x35); // Set the VCOMH voltage (0x35 = 4.025v)
			send(0x3E); // Set the VCOML voltage (0x3E = -0.950v)
			send(COMMAND::VCOM2);
			send(0xBE);

			// MEMORY ACCESS CONTROL
			send(COMMAND::MAC);
			send(0x48);
			send(COMMAND::PIXEL_FORMAT);
			send(0x55); // 16bit/pixel
			send(COMMAND::FRC);
			send(0x1F);

			// DDRAM
			send(COMMAND::TEARING_OFF);
			send(COMMAND::DISPLAY_INVERSION);
			send(COMMAND::ENTRY_MODE_SET);
			// Deep Standby Mode: OFF
			// Set the output level of gate driver G1-G320: Normal display
			// Low voltage detection: Disable
			send(0x07);

			// DISPLAY
			// send(ILI9341_DFC); // display function control
			// Set the scan mode in non-display area
			// DeterMINe source/VCOM output in a non-display area in the partial display mode
			// sendData(0x0a);
			// Select whether the liquid crystal type is normally white type or normally black type
			// Sets the direction of scan by the gate driver in the range deterMINed by SCN and NL
			// Select the shift direction of outputs from the source driver
			// Sets the gate driver pin arrangement in combination with the GS bit to select the optimal scan mode for the module
			// Specify the scan cycle interval of gate driver in non-display area when PTG to select interval scan
			// sendData(0x82);
			// Sets the number of lines to drive the LCD at an interval of 8 lines
			// sendData(0x27); // clock divisor

			send(COMMAND::GRAM); // memory write
			delay_ms(200);
		}

		void Base::fill(Color color)
		{
			uint32_t pixels_to_color = WIDTH * HEIGHT;

			switch (rotation)
			{
				case ROTATION::PORTRAIT:
				case ROTATION::LANDSCAPE:
					set_window_location(
						Point { (uint16_t) (0        ), (uint16_t) (0         ) },
						Point { (uint16_t) (WIDTH - 1), (uint16_t) (HEIGHT - 1) });
					break;
				case ROTATION::REVERSE_PORTRAIT:
				case ROTATION::REVERSE_LANDSCAPE:
					set_window_location(
						Point { (uint16_t) (0         ), (uint16_t) (0        ) },
						Point { (uint16_t) (HEIGHT - 1), (uint16_t) (WIDTH - 1) });
					break;
			}

			while (pixels_to_color--) send(color);
		}
		void Base::draw_pixel(Point point, Color color)
		{
			set_window_location(point, point);
			send(color);
		}
		void Base::draw_full_rectangle(
			const Point point,
			const Size size,
			Color color)
		{
			uint32_t pixels_to_color = size.x * size.y;

			set_window_location(point, size);

			while (pixels_to_color--) send(color);
		}
		void Base::draw_buffer(Point point, Point size, const Color* data)
		{
			uint32_t pixels_to_color = size.x * size.y;

			set_window_location(point, size);

			while (pixels_to_color--) send(*data++);
		}
	}
}

/*

// void send(uint8_t com)
// {
// 	// 0b01100000000000000000000000000000
// 	*((volatile uint16_t*) 0x60000000) = com;
// }
// void send(uint16_t data)
// {
// 	// 0b01100000000010000000000000000000
// 	*((volatile uint16_t*) 0x60080000) = data;
// 	// *((volatile uint16_t*) 0x60040000) = data;
// }

void ILI9341_drawCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color)
{
	int16_t f = 1 - r;
	int16_t ddF_x = 1;
	int16_t ddF_y = -2 * r;
	int16_t x = 0;
	int16_t y = r;

	ILI9341_DrawPixel(x0  , y0+r, color);
	ILI9341_DrawPixel(x0  , y0-r, color);
	ILI9341_DrawPixel(x0+r, y0  , color);
	ILI9341_DrawPixel(x0-r, y0  , color);

	while (x < y)
	{
		if (f >= 0)
		{
			ddF_y += 2;
			f += ddF_y;

			y--;
		}

		ddF_x += 2;
		f += ddF_x;
		x++;

		ILI9341_DrawPixel(x0 + x, y0 + y, color);
		ILI9341_DrawPixel(x0 - x, y0 + y, color);
		ILI9341_DrawPixel(x0 + x, y0 - y, color);
		ILI9341_DrawPixel(x0 - x, y0 - y, color);
		ILI9341_DrawPixel(x0 + y, y0 + x, color);
		ILI9341_DrawPixel(x0 - y, y0 + x, color);
		ILI9341_DrawPixel(x0 + y, y0 - x, color);
		ILI9341_DrawPixel(x0 - y, y0 - x, color);
	}
}
static void drawCircleHelper( int16_t x0, int16_t y0, int16_t r, uint8_t cornername, uint16_t color)
{
	int16_t f     = 1 - r;
	int16_t ddF_x = 1;
	int16_t ddF_y = -2 * r;
	int16_t x     = 0;
	int16_t y     = r;

	while (x<y)
	{
		if (f >= 0)
		{
			y--;
			ddF_y += 2;
			f     += ddF_y;
		}

		x++;
		ddF_x += 2;
		f     += ddF_x;

		if (cornername & 0x4)
		{
			ILI9341_DrawPixel(x0 + x, y0 + y, color);
			ILI9341_DrawPixel(x0 + y, y0 + x, color);
		}
		if (cornername & 0x2)
		{
			ILI9341_DrawPixel(x0 + x, y0 - y, color);
			ILI9341_DrawPixel(x0 + y, y0 - x, color);
		}
		if (cornername & 0x8)
		{
			ILI9341_DrawPixel(x0 - y, y0 + x, color);
			ILI9341_DrawPixel(x0 - x, y0 + y, color);
		}
		if (cornername & 0x1)
		{
			ILI9341_DrawPixel(x0 - y, y0 - x, color);
			ILI9341_DrawPixel(x0 - x, y0 - y, color);
		}
	}
}

static void fillCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername, int16_t delta, uint16_t color)
{
	int16_t f     = 1 - r;
  int16_t ddF_x = 1;
  int16_t ddF_y = -2 * r;
  int16_t x     = 0;
  int16_t y     = r;

  while (x<y) {
    if (f >= 0) {
      y--;
      ddF_y += 2;
      f     += ddF_y;
    }
    x++;
    ddF_x += 2;
    f     += ddF_x;

    if (cornername & 0x1) {
      ILI9341_drawFastVLine(x0+x, y0-y, 2*y+1+delta, color);
      ILI9341_drawFastVLine(x0+y, y0-x, 2*x+1+delta, color);
    }
    if (cornername & 0x2) {
      ILI9341_drawFastVLine(x0-x, y0-y, 2*y+1+delta, color);
      ILI9341_drawFastVLine(x0-y, y0-x, 2*x+1+delta, color);
    }
  }
}
void ILI9341_fillCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color)
{
	ILI9341_drawFastVLine(x0, y0-r, 2*r+1, color);
  fillCircleHelper(x0, y0, r, 3, 0, color);
}

//9. Line drawing functions
void ILI9341_drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color)
{
	int16_t steep = abs(y1 - y0) > abs(x1 - x0);
  if (steep) {
    swap(x0, y0);
    swap(x1, y1);
  }

  if (x0 > x1) {
    swap(x0, x1);
    swap(y0, y1);
  }

  int16_t dx, dy;
  dx = x1 - x0;
  dy = abs(y1 - y0);

  int16_t err = dx / 2;
  int16_t ystep;

  if (y0 < y1) {
    ystep = 1;
  } else {
    ystep = -1;
  }

  for (; x0<=x1; x0++) {
    if (steep) {
      ILI9341_DrawPixel(y0, x0, color);
    } else {
      ILI9341_DrawPixel(x0, y0, color);
    }
    err -= dy;
    if (err < 0) {
      y0 += ystep;
      err += dx;
    }
  }
}

void ILI9341_drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color)
{
	ILI9341_drawLine(x, y, x+w-1, y, color);
}

void ILI9341_drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color)
{
	ILI9341_drawLine(x, y, x, y+h-1, color);
}
void ILI9341_drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color)
{
	ILI9341_drawLine(x0, y0, x1, y1, color);
	ILI9341_drawLine(x1, y1, x2, y2, color);
	ILI9341_drawLine(x2, y2, x0, y0, color);
}
void ILI9341_fillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color)
{
	int16_t a, b, y, last;

  // Sort coordinates by Y order (y2 >= y1 >= y0)
  if (y0 > y1) {
    swap(y0, y1); swap(x0, x1);
  }
  if (y1 > y2) {
    swap(y2, y1); swap(x2, x1);
  }
  if (y0 > y1) {
    swap(y0, y1); swap(x0, x1);
  }

  if(y0 == y2) { // Handle awkward all-on-same-line case as its own thing
    a = b = x0;
    if(x1 < a)      a = x1;
    else if(x1 > b) b = x1;
    if(x2 < a)      a = x2;
    else if(x2 > b) b = x2;
    ILI9341_drawFastHLine(a, y0, b-a+1, color);
    return;
  }

  int16_t
    dx01 = x1 - x0,
    dy01 = y1 - y0,
    dx02 = x2 - x0,
    dy02 = y2 - y0,
    dx12 = x2 - x1,
    dy12 = y2 - y1,
    sa   = 0,
    sb   = 0;

  // For upper part of triangle, find scanline crossings for segments
  // 0-1 and 0-2.  If y1=y2 (flat-bottomed triangle), the scanline y1
  // is included here (and second loop will be skipped, avoiding a /0
  // error there), otherwise scanline y1 is skipped here and handled
  // in the second loop...which also avoids a /0 error here if y0=y1
  // (flat-topped triangle).
  if(y1 == y2) last = y1;   // Include y1 scanline
  else         last = y1-1; // Skip it

  for(y=y0; y<=last; y++) {
    a   = x0 + sa / dy01;
    b   = x0 + sb / dy02;
    sa += dx01;
    sb += dx02;

    if(a > b) swap(a,b);
    ILI9341_drawFastHLine(a, y, b-a+1, color);
  }

  // For lower part of triangle, find scanline crossings for segments
  // 0-2 and 1-2.  This loop is skipped if y1=y2.
  sa = dx12 * (y - y1);
  sb = dx02 * (y - y0);
  for(; y<=y2; y++) {
    a   = x1 + sa / dy12;
    b   = x0 + sb / dy02;
    sa += dx12;
    sb += dx02;

    if(a > b) swap(a,b);
    ILI9341_drawFastHLine(a, y, b-a+1, color);
	}
}

//11. Text printing functions
void ILI9341_drawChar(int16_t x, int16_t y, unsigned char c, uint16_t color, uint16_t bg, uint8_t size)
{
	if((x >= ILI9341_WIDTH)            || // Clip right
     (y >= ILI9341_HEIGHT)           || // Clip bottom
     ((x + 6 * size - 1) < 0) || // Clip left
     ((y + 8 * size - 1) < 0))   // Clip top
    return;

  if(!_cp437 && (c >= 176)) c++; // Handle 'classic' charset behavior

  for (int8_t i=0; i<6; i++ ) {
    uint8_t line;
    if (i == 5)
      line = 0x0;
    else
      line = pgm_read_byte(font1+(c*5)+i);
    for (int8_t j = 0; j<8; j++) {
      if (line & 0x1) {
        if (size == 1) // default size
          ILI9341_DrawPixel(x+i, y+j, color);
        else {  // big size
          ILI9341_Fill_Rect(x+(i*size), y+(j*size), size + x+(i*size), size+1 + y+(j*size), color);
        }
      } else if (bg != color) {
        if (size == 1) // default size
          ILI9341_DrawPixel(x+i, y+j, bg);
        else {  // big size
          ILI9341_Fill_Rect(x+i*size, y+j*size, size + x+i*size, size+1 + y+j*size, bg);
        }
      }
      line >>= 1;
    }
  }
}
void ILI9341_printText(char text[], int16_t x, int16_t y, uint16_t color, uint16_t bg, uint8_t size)
{
	int16_t offset;
	offset = size*6;
	for(uint16_t i=0; i<40 && text[i]!=NULL; i++)
	{
		ILI9341_drawChar(x+(offset*i), y, text[i],color,bg,size);
	}
}
*/

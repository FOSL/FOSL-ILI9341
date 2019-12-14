// GETTERS
template <typename TColor>
uint16_t Base<TColor>::get_width(void) const
{
	switch(rotation)
	{
		case ROTATION::PORTRAIT:
		case ROTATION::REVERSE_PORTRAIT:
			return 240;

		case ROTATION::LANDSCAPE:
		case ROTATION::REVERSE_LANDSCAPE:
			return 320;

		default:
			assert(!"INVALID ROTATION");
			return 0;
	}
}
template <typename TColor>
uint16_t Base<TColor>::get_height(void) const
{
	switch(rotation)
	{
		case ROTATION::PORTRAIT:
		case ROTATION::REVERSE_PORTRAIT:
			return 320;

		case ROTATION::LANDSCAPE:
		case ROTATION::REVERSE_LANDSCAPE:
			return 240;

		default:
			assert(!"INVALID ROTATION");
			return 0;
	}
}

// SETTERS
template <typename TColor>
void Base<TColor>::set_window_location(Point point, Size size)
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
template <typename TColor>
void Base<TColor>::set(ROTATION rotation)
{
	static const uint8_t MY  = BIT(7);
	static const uint8_t MX  = BIT(6);
	static const uint8_t MV  = BIT(5);
	// static const uint8_t ML  = BIT();
	// static const uint8_t BGR  = BIT();

	this->rotation = rotation;

	send(COMMAND::MAC);
	switch(rotation)
	{
		case ROTATION::PORTRAIT:          send(00 | MY | 00); break;
		case ROTATION::LANDSCAPE:         send(00 | 00 | MV); break;
		case ROTATION::REVERSE_PORTRAIT:  send(MX | 00 | 00); break;
		case ROTATION::REVERSE_LANDSCAPE: send(MX | MY | MV); break;
	}
}

// METHODS
template <typename TColor>
void Base<TColor>::initialize(void)
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
	send(COMMAND::PIXEL_FORMAT);
	send(0x55); // 16bit/pixel
	send(COMMAND::FRC); // SET FRAMERATE
	send(0b00);         // fosc / 1
	send(0b11101);      // 63 FPS
	// send(0b10000);      // 119 FPS

	// DDRAM
	send(COMMAND::TEARING_OFF);
	// send(COMMAND::DISPLAY_INVERSION);
	send(COMMAND::ENTRY_MODE_SET);
	// Deep Standby Mode: OFF
	// Set the output level of gate driver G1-G320: Normal display
	// Low voltage detection: Disable
	send(0x07);

	// DISPLAY
	// send(COMMAND::DFC); // display function control
	// Set the scan mode in non-display area
	// DeterMINe source/VCOM output in a non-display area in the partial display mode
	// send(0x0a);
	// Select whether the liquid crystal type is normally white type or normally black type
	// Sets the direction of scan by the gate driver in the range deterMINed by SCN and NL
	// Select the shift direction of outputs from the source driver
	// Sets the gate driver pin arrangement in combination with the GS bit to select the optimal scan mode for the module
	// Specify the scan cycle interval of gate driver in non-display area when PTG to select interval scan
	// send(0x82);
	// Sets the number of lines to drive the LCD at an interval of 8 lines
	// send(0x27); // clock divisor

	send(COMMAND::GRAM); // memory write
	delay_ms(200);
}

/*
template <typename TColor>
void Base<TColor>::fill(TColor color)
{
	uint32_t pixels_to_color = get_width() * get_height();

// 	switch (rotation)
// 	{
// 		case ROTATION::PORTRAIT:
// 		case ROTATION::LANDSCAPE:
// 			set_window_location(
// 				Point { (uint16_t) (0        ), (uint16_t) (0         ) },
// 				Point { (uint16_t) (WIDTH - 1), (uint16_t) (HEIGHT - 1) });
// 			break;
// 		case ROTATION::REVERSE_PORTRAIT:
// 		case ROTATION::REVERSE_LANDSCAPE:
// 			set_window_location(
// 				Point { (uint16_t) (0         ), (uint16_t) (0        ) },
// 				Point { (uint16_t) (HEIGHT - 1), (uint16_t) (WIDTH - 1) });
// 			break;
// 	}

	set_window_location(
		Point { (uint16_t) (0              ), (uint16_t) (0               ) },
		Point { (uint16_t) (get_width() - 1), (uint16_t) (get_height() - 1) });

	while (pixels_to_color--) send(color);
}
*/
template <typename TColor>
void Base<TColor>::draw_pixel(Point point, TColor color)
{
	set_window_location(point, Size { 1, 1 });

	send(color);
}
template <typename TColor>
void Base<TColor>::draw_full_rectangle(
	Point point,
	const Size size,
	TColor color)
{
	set_window_location(point, size);

	for (uint32_t pixels_to_color = size.x * size.y; pixels_to_color; pixels_to_color--)
		send(color);
}
template <typename TColor>
void Base<TColor>::draw_buffer(Point point, Size size, const TColor* data)
{
	set_window_location(point, size);

	for (uint32_t pixels_to_color = size.x * size.y; pixels_to_color; pixels_to_color--)
		send(*data++);
}

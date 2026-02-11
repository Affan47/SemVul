expected_message_length(unsigned char status, const unsigned char *second_byte, const size_t buffer_length)
{

	assert(is_status_byte(status));


	assert(!is_sysex_byte(status));


	assert(!is_escape_byte(status));


	if (status == 0xFF) {
		if (buffer_length < 2) {
			g_critical("SMF error: end of buffer in expected_message_length().");
			return (-1);
		}


		return (*(second_byte + 1) + 3);
	}

	if ((status & 0xF0) == 0xF0) {
		switch (status) {
			case 0xF2:
				return (3);

			case 0xF1:
			case 0xF3:
				return (2);

			case 0xF6:
			case 0xF8:
			case 0xF9:
			case 0xFA:
			case 0xFB:
			case 0xFC:
			case 0xFE:
				return (1);

			default:
				g_critical("SMF error: unknown 0xFx-type status byte '0x%x'.", status);
				return (-2);
		}
	}


	status &= 0xF0;

	switch (status) {
		case 0x80:
		case 0x90:
		case 0xA0:
		case 0xB0:
		case 0xE0:
			return (3);

		case 0xC0:
		case 0xD0:
			return (2);

		default:
			g_critical("SMF error: unknown status byte '0x%x'.", status);
			return (-3);
	}
}

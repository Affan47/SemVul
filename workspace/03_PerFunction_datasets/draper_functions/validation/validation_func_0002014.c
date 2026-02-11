get_platform_PORT(Uint8 *s0, Uint8 *s1)
{
	int stick0, stick1;
	stick0 = stick1 = INPUT_STICK_CENTRE;

	if (PLATFORM_kbd_joy_0_enabled) {
		if (kbhits[KBD_STICK_0_LEFT])
			stick0 &= INPUT_STICK_LEFT;
		if (kbhits[KBD_STICK_0_RIGHT])
			stick0 &= INPUT_STICK_RIGHT;
		if (kbhits[KBD_STICK_0_UP])
			stick0 &= INPUT_STICK_FORWARD;
		if (kbhits[KBD_STICK_0_DOWN])
			stick0 &= INPUT_STICK_BACK;
	}
	if (PLATFORM_kbd_joy_1_enabled) {
		if (kbhits[KBD_STICK_1_LEFT])
			stick1 &= INPUT_STICK_LEFT;
		if (kbhits[KBD_STICK_1_RIGHT])
			stick1 &= INPUT_STICK_RIGHT;
		if (kbhits[KBD_STICK_1_UP])
			stick1 &= INPUT_STICK_FORWARD;
		if (kbhits[KBD_STICK_1_DOWN])
			stick1 &= INPUT_STICK_BACK;
	}

	if (swap_joysticks) {
		*s1 = stick0;
		*s0 = stick1;
	}
	else {
		*s0 = stick0;
		*s1 = stick1;
	}

	if ((joystick0 != NULL) || (joystick1 != NULL))
	{
		SDL_JoystickUpdate();
	}

	if (fd_joystick0 != -1)
		*s0 &= get_LPT_joystick_state(fd_joystick0);
	else if (joystick0 != NULL)
		*s0 &= get_SDL_joystick_state(joystick0);

	if (fd_joystick1 != -1)
		*s1 &= get_LPT_joystick_state(fd_joystick1);
	else if (joystick1 != NULL)
		*s1 &= get_SDL_joystick_state(joystick1);
}

internal_code_pressed(InputCode code)
{
	const struct KeyboardInfo *keyinfo;
	const struct JoystickInfo *joyinfo;

	assert( code < code_mac );

	if (code < __code_max)
	{
		switch (code_map[code].type)
		{
			case CODE_TYPE_KEYBOARD :
				keyinfo = internal_code_find_keyboard(code);
				if (keyinfo)
					return osd_is_key_pressed(keyinfo->code);
				break;
			case CODE_TYPE_JOYSTICK :
				joyinfo = internal_code_find_joystick(code);
				if (joyinfo)
					return osd_is_joy_pressed(joyinfo->code);
				break;
		}
	} else {
		switch (code_map[code].type)
		{
			case CODE_TYPE_KEYBOARD :
				return osd_is_key_pressed(code_map[code].oscode);
			case CODE_TYPE_JOYSTICK :
				return osd_is_joy_pressed(code_map[code].oscode);
		}
	}
	return 0;
}

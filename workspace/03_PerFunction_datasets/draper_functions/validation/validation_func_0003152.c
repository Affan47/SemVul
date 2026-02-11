EyeboxOne_parse_keypad_setting (Driver *drvthis, char * keyname, char default_value)
{
	char return_val = 0;
	const char *s;
	char buf[255];

	s = drvthis->config_get_string(drvthis->name, keyname, 0, NULL);
	if (s != NULL) {
		strncpy(buf, s, sizeof(buf));
		buf[sizeof(buf)-1] = '\0';
		return_val = buf[0];
	} else {
		return_val = default_value;
	}
	return return_val;
}

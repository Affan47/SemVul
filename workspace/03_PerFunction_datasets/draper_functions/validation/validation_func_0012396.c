CFontz633_get_key (Driver *drvthis)
{

	unsigned char key = GetKeyFromKeyRing(&keyring);

	switch (key) {
		case CF633_KEY_LEFT:
			return "Left";
			break;
		case CF633_KEY_UP:
			return "Up";
			break;
		case CF633_KEY_DOWN:
			return "Down";
			break;
		case CF633_KEY_RIGHT:
			return "Right";
			break;
		case CF633_KEY_ENTER:
			return "Enter";
			break;
		case CF633_KEY_ESCAPE:
			return "Escape";
			break;
		default:
			if (key != '\0')
				report(RPT_INFO, "%s: Untreated key 0x%02X", drvthis->name, key);
			return NULL;
			break;
	}
	return NULL;
}

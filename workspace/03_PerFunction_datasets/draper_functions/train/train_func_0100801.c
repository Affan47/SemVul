select_interface (int modprobe)
{
	int fd;

	char *modules[] = {"hdaps_ec", "hdaps", "ams"};
	int mod_index;
	char command[64];

	if (modprobe) {
		for (mod_index = 0; mod_index < sizeof(modules)/sizeof(modules[0]); mod_index++) {
			snprintf(command, sizeof(command), "modprobe %s 1>/dev/null 2>/dev/null", modules[mod_index]);
			system(command);
		}
	}

	fd = open (HDAPS_POSITION_FILE, O_RDONLY);
	if (fd < 0) {
		fd = open(AMS_POSITION_FILE, O_RDONLY);
		if (fd < 0) {
			position_interface = INTERFACE_NONE;
		}
		else {
			close(fd);
			position_interface = INTERFACE_AMS;
		}
	}
	else {
		close(fd);
		position_interface = INTERFACE_HDAPS;
	}
	return position_interface;
}

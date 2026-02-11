is_command_allowed_in_ps(u16 cmd)
{
	switch (cmd) {
	case CMD_802_11_RSSI:
		return 1;
	case CMD_802_11_HOST_SLEEP_CFG:
		return 1;
	default:
		break;
	}
	return 0;
}

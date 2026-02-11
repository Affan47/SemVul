c_set_power(const char* origin, gboolean on)
{
	LOG(LOG_DEBUG, "Enter");
	if (on)
	{
		if (serial.state == MUX_STATE_OFF)
		{
			LOG(LOG_INFO, "power on");
			serial.state = MUX_STATE_OPENING;
			watchdog(&serial);
		}
		else
			LOG(LOG_WARNING, "power on request received but was already on");
	}
	else
	{
		if (serial.state == MUX_STATE_MUXING)
		{
			LOG(LOG_INFO, "power off");
			g_source_remove(serial.g_source_watchdog);
			close_devices();
		}
		else
			LOG(LOG_WARNING, "power off received but wasn't on/muxing");
	}
	LOG(LOG_DEBUG, "Leave");
	return TRUE;
}

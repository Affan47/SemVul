NK7110_SetAlarm(gn_data *data, struct gn_statemachine *state)
{
	unsigned char req[] = {FBUS_FRAME_HEADER, 0x6b, 0x01, 0x20, 0x03,
				0x02,
				0x00, 0x00,
				0x00};

	if (!data->alarm) return GN_ERR_INTERNALERROR;

	if (data->alarm->enabled) {
		req[7] = NK7110_ALARM_ENABLED;
		req[8] = data->alarm->timestamp.hour;
		req[9] = data->alarm->timestamp.minute;
	} else {
		req[7] = NK7110_ALARM_DISABLED;
	}

	SEND_MESSAGE_BLOCK(NK7110_MSG_CLOCK, 11);
}

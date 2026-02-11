adsi_unload_session(struct ast_channel *chan)
{
	unsigned char dsp[256] = "";
	int bytes = 0;


	bytes += adsi_disconnect_session(dsp + bytes);
	bytes += adsi_voice_mode(dsp + bytes, 0);


	if (adsi_transmit_message_full(chan, dsp, bytes, ADSI_MSG_DISPLAY, 0)) {
		return -1;
	}

	return 0;
}

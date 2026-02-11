sco_cb(GIOChannel *chan, GIOCondition cond,
			struct audio_device *device)
{
	if (cond & G_IO_NVAL)
		return FALSE;

	error("Audio connection got disconnected");

	pending_connect_finalize(device);
	headset_set_state(device, HEADSET_STATE_CONNECTED);

	return FALSE;
}

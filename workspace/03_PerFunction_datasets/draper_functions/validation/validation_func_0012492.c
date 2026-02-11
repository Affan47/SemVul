lme2510_stream_restart(struct dvb_usb_device *d)
{
	struct lme2510_state *st = d->priv;
	u8 all_pids[] = LME_ALL_PIDS;
	u8 stream_on[] = LME_ST_ON_W;
	int ret;
	u8 rbuff[1];
	if (st->pid_off)
		ret = lme2510_usb_talk(d, all_pids, sizeof(all_pids),
			rbuff, sizeof(rbuff));

	ret = lme2510_usb_talk(d, stream_on, sizeof(stream_on),
			rbuff, sizeof(rbuff));
	return ret;
}

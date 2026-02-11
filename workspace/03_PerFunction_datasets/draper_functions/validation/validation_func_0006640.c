vp702x_fe_set_tone(struct dvb_frontend *fe,
			      enum fe_sec_tone_mode tone)
{
	struct vp702x_fe_state *st = fe->demodulator_priv;
	struct vp702x_device_state *dst = st->d->priv;
	u8 *buf;

	deb_fe("%s\n",__func__);

	st->tone_mode = tone;

	if (tone == SEC_TONE_ON)
		st->lnb_buf[2] = 0x02;
	else
		st->lnb_buf[2] = 0x00;

	st->lnb_buf[7] = vp702x_chksum(st->lnb_buf, 0, 7);

	mutex_lock(&dst->buf_mutex);

	buf = dst->buf;
	memcpy(buf, st->lnb_buf, 8);

	vp702x_usb_inout_op(st->d, buf, 8, buf, 10, 100);
	if (buf[2] == 0 && buf[3] == 0)
		deb_fe("set_tone cmd failed.\n");
	else
		deb_fe("set_tone cmd succeeded.\n");

	mutex_unlock(&dst->buf_mutex);

	return 0;
}

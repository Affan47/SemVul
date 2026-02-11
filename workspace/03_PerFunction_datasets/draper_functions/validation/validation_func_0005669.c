tda8295_power(struct dvb_frontend *fe, int enable)
{
	struct tda8290_priv *priv = fe->analog_demod_priv;
	unsigned char buf[] = { 0x30, 0x00 };

	tuner_i2c_xfer_send_recv(&priv->i2c_props, &buf[0], 1, &buf[1], 1);

	if (enable)
		buf[1] = 0x01;
	else
		buf[1] = 0x03;

	tuner_i2c_xfer_send(&priv->i2c_props, buf, 2);
}

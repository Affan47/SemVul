microtune_mt7202dtf_tuner_set_params(struct dvb_frontend *fe)
{
	struct dtv_frontend_properties *c = &fe->dtv_property_cache;
	struct dvb_bt8xx_card *card = (struct dvb_bt8xx_card *) fe->dvb->priv;
	u8 cfg, cpump, band_select;
	u8 data[4];
	u32 div;
	struct i2c_msg msg = { .addr = 0x60, .flags = 0, .buf = data, .len = sizeof(data) };

	div = (36000000 + c->frequency + 83333) / 166666;
	cfg = 0x88;

	if (c->frequency < 175000000)
		cpump = 2;
	else if (c->frequency < 390000000)
		cpump = 1;
	else if (c->frequency < 470000000)
		cpump = 2;
	else if (c->frequency < 750000000)
		cpump = 2;
	else
		cpump = 3;

	if (c->frequency < 175000000)
		band_select = 0x0e;
	else if (c->frequency < 470000000)
		band_select = 0x05;
	else
		band_select = 0x03;

	data[0] = (div >> 8) & 0x7f;
	data[1] = div & 0xff;
	data[2] = ((div >> 10) & 0x60) | cfg;
	data[3] = (cpump << 6) | band_select;

	if (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);
	i2c_transfer(card->i2c_adapter, &msg, 1);
	return (div * 166666 - 36000000);
}

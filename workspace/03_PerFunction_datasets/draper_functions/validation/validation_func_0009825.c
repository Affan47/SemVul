stb6000_sleep(struct dvb_frontend *fe)
{
	struct stb6000_priv *priv = fe->tuner_priv;
	int ret;
	u8 buf[] = { 10, 0 };
	struct i2c_msg msg = {
		.addr = priv->i2c_address,
		.flags = 0,
		.buf = buf,
		.len = 2
	};

	dprintk("%s:\n", __func__);

	if (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);

	ret = i2c_transfer(priv->i2c, &msg, 1);
	if (ret != 1)
		dprintk("%s: i2c error\n", __func__);

	if (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 0);

	return (ret == 1) ? 0 : ret;
}

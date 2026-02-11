cx24120_tune(struct dvb_frontend *fe, bool re_tune,
			unsigned int mode_flags, unsigned int *delay,
			enum fe_status *status)
{
	struct cx24120_state *state = fe->demodulator_priv;
	int ret;

	dev_dbg(&state->i2c->dev, "(%d)\n", re_tune);


	if (re_tune) {
		ret = cx24120_set_frontend(fe);
		if (ret)
			return ret;
	}

	return cx24120_read_status(fe, status);
}

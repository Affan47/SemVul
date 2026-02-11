si2165_read_status(struct dvb_frontend *fe, enum fe_status *status)
{
	int ret;
	u8 fec_lock = 0;
	struct si2165_state *state = fe->demodulator_priv;

	if (!state->has_dvbt)
		return -EINVAL;


	ret = si2165_readreg8(state, 0x4e0, &fec_lock);
	if (ret < 0)
		return ret;
	*status = 0;
	if (fec_lock & 0x01) {
		*status |= FE_HAS_SIGNAL;
		*status |= FE_HAS_CARRIER;
		*status |= FE_HAS_VITERBI;
		*status |= FE_HAS_SYNC;
		*status |= FE_HAS_LOCK;
	}

	return 0;
}

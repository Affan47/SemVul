static int mb86a20s_get_pre_ber(struct dvb_frontend *fe,
				unsigned layer,
				u32 *error, u32 *count)
{
	struct mb86a20s_state *state = fe->demodulator_priv;
	int rc, val;

	dev_dbg(&state->i2c->dev, "%s called.\n", __func__);

	if (layer >= NUM_LAYERS)
		return -EINVAL;


	rc = mb86a20s_readreg(state, 0x54);
	if (rc < 0)
		return rc;


	if (!(rc & (1 << layer))) {
		dev_dbg(&state->i2c->dev,
			"%s: preBER for layer %c is not available yet.\n",
			__func__, 'A' + layer);
		return -EBUSY;
	}


	rc = mb86a20s_readreg(state, 0x55 + layer * 3);
	if (rc < 0)
		return rc;
	*error = rc << 16;
	rc = mb86a20s_readreg(state, 0x56 + layer * 3);
	if (rc < 0)
		return rc;
	*error |= rc << 8;
	rc = mb86a20s_readreg(state, 0x57 + layer * 3);
	if (rc < 0)
		return rc;
	*error |= rc;

	dev_dbg(&state->i2c->dev,
		"%s: bit error before Viterbi for layer %c: %d.\n",
		__func__, 'A' + layer, *error);


	rc = mb86a20s_writereg(state, 0x50, 0xa7 + layer * 3);
	if (rc < 0)
		return rc;
	rc = mb86a20s_readreg(state, 0x51);
	if (rc < 0)
		return rc;
	*count = rc << 16;
	rc = mb86a20s_writereg(state, 0x50, 0xa8 + layer * 3);
	if (rc < 0)
		return rc;
	rc = mb86a20s_readreg(state, 0x51);
	if (rc < 0)
		return rc;
	*count |= rc << 8;
	rc = mb86a20s_writereg(state, 0x50, 0xa9 + layer * 3);
	if (rc < 0)
		return rc;
	rc = mb86a20s_readreg(state, 0x51);
	if (rc < 0)
		return rc;
	*count |= rc;

	dev_dbg(&state->i2c->dev,
		"%s: bit count before Viterbi for layer %c: %d.\n",
		__func__, 'A' + layer, *count);


	if (state->estimated_rate[layer]
	    && state->estimated_rate[layer] != *count) {
		dev_dbg(&state->i2c->dev,
			"%s: updating layer %c preBER counter to %d.\n",
			__func__, 'A' + layer, state->estimated_rate[layer]);


		rc = mb86a20s_writereg(state, 0x52, 0x00);


		rc = mb86a20s_writereg(state, 0x50, 0xa7 + layer * 3);
		if (rc < 0)
			return rc;
		rc = mb86a20s_writereg(state, 0x51,
				       state->estimated_rate[layer] >> 16);
		if (rc < 0)
			return rc;
		rc = mb86a20s_writereg(state, 0x50, 0xa8 + layer * 3);
		if (rc < 0)
			return rc;
		rc = mb86a20s_writereg(state, 0x51,
				       state->estimated_rate[layer] >> 8);
		if (rc < 0)
			return rc;
		rc = mb86a20s_writereg(state, 0x50, 0xa9 + layer * 3);
		if (rc < 0)
			return rc;
		rc = mb86a20s_writereg(state, 0x51,
				       state->estimated_rate[layer]);
		if (rc < 0)
			return rc;


		rc = mb86a20s_writereg(state, 0x52, 0x01);


		rc = mb86a20s_writereg(state, 0x53, 0x00);
		if (rc < 0)
			return rc;
		rc = mb86a20s_writereg(state, 0x53, 0x07);
	} else {

		rc = mb86a20s_readreg(state, 0x53);
		if (rc < 0)
			return rc;
		val = rc;
		rc = mb86a20s_writereg(state, 0x53, val & ~(1 << layer));
		if (rc < 0)
			return rc;
		rc = mb86a20s_writereg(state, 0x53, val | (1 << layer));
	}

	return rc;
}

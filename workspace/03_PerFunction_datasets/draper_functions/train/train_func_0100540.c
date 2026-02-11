zl10353_attach(const struct zl10353_config *config,
				    struct i2c_adapter *i2c)
{
	struct zl10353_state *state = NULL;
	int id;


	state = kzalloc(sizeof(struct zl10353_state), GFP_KERNEL);
	if (state == NULL)
		goto error;


	state->i2c = i2c;
	memcpy(&state->config, config, sizeof(struct zl10353_config));


	id = zl10353_read_register(state, CHIP_ID);
	if ((id != ID_ZL10353) && (id != ID_CE6230) && (id != ID_CE6231))
		goto error;


	memcpy(&state->frontend.ops, &zl10353_ops, sizeof(struct dvb_frontend_ops));
	state->frontend.demodulator_priv = state;

	return &state->frontend;
error:
	kfree(state);
	return NULL;
}

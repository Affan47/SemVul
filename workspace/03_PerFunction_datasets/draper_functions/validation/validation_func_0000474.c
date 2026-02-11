mt2063_attach(struct dvb_frontend *fe,
				   struct mt2063_config *config,
				   struct i2c_adapter *i2c)
{
	struct mt2063_state *state = NULL;

	dprintk(2, "\n");

	state = kzalloc(sizeof(struct mt2063_state), GFP_KERNEL);
	if (!state)
		return NULL;

	state->config = config;
	state->i2c = i2c;
	state->frontend = fe;
	state->reference = config->refclock / 1000;
	fe->tuner_priv = state;
	fe->ops.tuner_ops = mt2063_ops;

	printk(KERN_INFO "%s: Attaching MT2063\n", __func__);
	return fe;
}

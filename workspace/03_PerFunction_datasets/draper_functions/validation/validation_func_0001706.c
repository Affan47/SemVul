ts2020_sleep(struct dvb_frontend *fe)
{
	struct ts2020_priv *priv = fe->tuner_priv;
	int ret;
	u8 u8tmp;

	if (priv->tuner == TS2020_M88TS2020)
		u8tmp = 0x0a;
	else
		u8tmp = 0x00;

	ret = regmap_write(priv->regmap, u8tmp, 0x00);
	if (ret < 0)
		return ret;


	if (!priv->dont_poll)
		cancel_delayed_work_sync(&priv->stat_work);
	return 0;
}

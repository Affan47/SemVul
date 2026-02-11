set_agc_config(struct atbm_state *priv,
	u8 min, u8 max, u8 hold_loop)
{

	if (!min && !max)
	    return 0;

	atbm8830_write_reg(priv, REG_AGC_MIN, min);
	atbm8830_write_reg(priv, REG_AGC_MAX, max);
	atbm8830_write_reg(priv, REG_AGC_HOLD_LOOP, hold_loop);

	return 0;
}

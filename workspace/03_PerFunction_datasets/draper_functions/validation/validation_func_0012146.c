lp8788_backlight_configure(struct lp8788_bl *bl)
{
	struct lp8788_backlight_platform_data *pdata = bl->pdata;
	struct lp8788_bl_config *cfg = &default_bl_config;
	int ret;
	u8 val;


	if (pdata) {
		cfg->bl_mode    = pdata->bl_mode;
		cfg->dim_mode   = pdata->dim_mode;
		cfg->full_scale = pdata->full_scale;
		cfg->rise_time  = pdata->rise_time;
		cfg->fall_time  = pdata->fall_time;
		cfg->pwm_pol    = pdata->pwm_pol;
	}


	val = (cfg->rise_time << LP8788_BL_RAMP_RISE_SHIFT) | cfg->fall_time;
	ret = lp8788_write_byte(bl->lp, LP8788_BL_RAMP, val);
	if (ret)
		return ret;


	val = (cfg->full_scale << LP8788_BL_FULLSCALE_SHIFT) |
		(cfg->dim_mode << LP8788_BL_DIM_MODE_SHIFT);


	switch (cfg->bl_mode) {
	case LP8788_BL_REGISTER_ONLY:
		val |= LP8788_BL_EN;
		break;
	case LP8788_BL_COMB_PWM_BASED:
	case LP8788_BL_COMB_REGISTER_BASED:
		val |= LP8788_BL_EN | LP8788_BL_PWM_INPUT_EN |
			(cfg->pwm_pol << LP8788_BL_PWM_POLARITY_SHIFT);
		break;
	default:
		dev_err(bl->lp->dev, "invalid mode: %d\n", cfg->bl_mode);
		return -EINVAL;
	}

	bl->mode = cfg->bl_mode;

	return lp8788_write_byte(bl->lp, LP8788_BL_CONFIG, val);
}

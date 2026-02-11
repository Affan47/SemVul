msm_hsusb_config_vddcx(struct msm_otg *motg, int high)
{
	int max_vol = motg->vdd_levels[VDD_LEVEL_MAX];
	int min_vol;
	int ret;

	if (high)
		min_vol = motg->vdd_levels[VDD_LEVEL_MIN];
	else
		min_vol = motg->vdd_levels[VDD_LEVEL_NONE];

	ret = regulator_set_voltage(motg->vddcx, min_vol, max_vol);
	if (ret) {
		pr_err("Cannot set vddcx voltage\n");
		return ret;
	}

	pr_debug("%s: min_vol:%d max_vol:%d\n", __func__, min_vol, max_vol);

	return ret;
}

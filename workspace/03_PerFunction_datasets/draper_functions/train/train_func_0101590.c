tps65910_ck32k_init(struct tps65910 *tps65910,
					struct tps65910_board *pmic_pdata)
{
	int ret;

	if (!pmic_pdata->en_ck32k_xtal)
		return 0;

	ret = tps65910_reg_clear_bits(tps65910, TPS65910_DEVCTRL,
						DEVCTRL_CK32K_CTRL_MASK);
	if (ret < 0) {
		dev_err(tps65910->dev, "clear ck32k_ctrl failed: %d\n", ret);
		return ret;
	}

	return 0;
}

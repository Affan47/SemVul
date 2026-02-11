brcms_c_antsel_antcfg2antsel(struct antsel_info *asi, u8 ant_cfg)
{
	u8 idx = BRCMS_ANTIDX_11N(BRCMS_ANTSEL_11N(ant_cfg));
	u16 mimo_antsel = 0;

	if (asi->antsel_type == ANTSEL_2x4) {

		mimo_antsel = (mimo_2x4_div_antselpat_tbl[idx] & 0xf);
		return mimo_antsel;

	} else if (asi->antsel_type == ANTSEL_2x3) {

		mimo_antsel = (mimo_2x3_div_antselpat_tbl[idx] & 0xf);
		return mimo_antsel;
	}

	return mimo_antsel;
}

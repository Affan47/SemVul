mrf24j40_set_txpower(struct ieee802154_hw *hw, s32 mbm)
{
	struct mrf24j40 *devrec = hw->priv;
	s32 small_scale;
	u8 val;

	if (0 >= mbm && mbm > -1000) {
		val = TXPWRL_0 << TXPWRL_SHIFT;
		small_scale = mbm;
	} else if (-1000 >= mbm && mbm > -2000) {
		val = TXPWRL_10 << TXPWRL_SHIFT;
		small_scale = mbm + 1000;
	} else if (-2000 >= mbm && mbm > -3000) {
		val = TXPWRL_20 << TXPWRL_SHIFT;
		small_scale = mbm + 2000;
	} else if (-3000 >= mbm && mbm > -4000) {
		val = TXPWRL_30 << TXPWRL_SHIFT;
		small_scale = mbm + 3000;
	} else {
		return -EINVAL;
	}

	switch (small_scale) {
	case 0:
		val |= (TXPWRS_0 << TXPWRS_SHIFT);
		break;
	case -50:
		val |= (TXPWRS_0_5 << TXPWRS_SHIFT);
		break;
	case -120:
		val |= (TXPWRS_1_2 << TXPWRS_SHIFT);
		break;
	case -190:
		val |= (TXPWRS_1_9 << TXPWRS_SHIFT);
		break;
	case -280:
		val |= (TXPWRS_2_8 << TXPWRS_SHIFT);
		break;
	case -370:
		val |= (TXPWRS_3_7 << TXPWRS_SHIFT);
		break;
	case -490:
		val |= (TXPWRS_4_9 << TXPWRS_SHIFT);
		break;
	case -630:
		val |= (TXPWRS_6_3 << TXPWRS_SHIFT);
		break;
	default:
		return -EINVAL;
	}

	return regmap_update_bits(devrec->regmap_long, REG_RFCON3,
				  TXPWRL_MASK | TXPWRS_MASK, val);
}

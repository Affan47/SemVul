carl9170_set_mac_tpc(struct ar9170 *ar, struct ieee80211_channel *channel)
{
	unsigned int power, chains;

	if (ar->eeprom.tx_mask != 1)
		chains = AR9170_TX_PHY_TXCHAIN_2;
	else
		chains = AR9170_TX_PHY_TXCHAIN_1;

	switch (channel->band) {
	case IEEE80211_BAND_2GHZ:
		power = ar->power_2G_ofdm[0] & 0x3f;
		break;
	case IEEE80211_BAND_5GHZ:
		power = ar->power_5G_leg[0] & 0x3f;
		break;
	default:
		BUG_ON(1);
	}

	power = min_t(unsigned int, power, ar->hw->conf.power_level * 2);

	carl9170_regwrite_begin(ar);
	carl9170_regwrite(AR9170_MAC_REG_ACK_TPC,
			  0x3c1e | power << 20 | chains << 26);
	carl9170_regwrite(AR9170_MAC_REG_RTS_CTS_TPC,
			  power << 5 | chains << 11 |
			  power << 21 | chains << 27);
	carl9170_regwrite(AR9170_MAC_REG_CFEND_QOSNULL_TPC,
			  power << 5 | chains << 11 |
			  power << 21 | chains << 27);
	carl9170_regwrite_finish();
	return carl9170_regwrite_result();
}

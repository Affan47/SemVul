rtl8821ae_dm_initialize_txpower_tracking_thermalmeter(
				struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_dm *rtldm = rtl_dm(rtlpriv);
	struct rtl_efuse *rtlefuse = rtl_efuse(rtlpriv);
	u8 default_swing_index  = 0;
	u8 p = 0;

	rtlpriv->dm.txpower_track_control = true;
	rtldm->thermalvalue = rtlefuse->eeprom_thermalmeter;
	rtldm->thermalvalue_iqk = rtlefuse->eeprom_thermalmeter;
	rtldm->thermalvalue_lck = rtlefuse->eeprom_thermalmeter;
	default_swing_index = rtl8821ae_dm_get_swing_index(hw);

	rtldm->default_ofdm_index =
		(default_swing_index == TXSCALE_TABLE_SIZE) ?
		24 : default_swing_index;
	rtldm->default_cck_index = 24;

	rtldm->swing_idx_cck_base = rtldm->default_cck_index;
	rtldm->cck_index = rtldm->default_cck_index;

	for (p = RF90_PATH_A; p < MAX_RF_PATH; ++p) {
		rtldm->swing_idx_ofdm_base[p] =
			rtldm->default_ofdm_index;
		rtldm->ofdm_index[p] = rtldm->default_ofdm_index;
		rtldm->delta_power_index[p] = 0;
		rtldm->power_index_offset[p] = 0;
		rtldm->delta_power_index_last[p] = 0;
	}
}

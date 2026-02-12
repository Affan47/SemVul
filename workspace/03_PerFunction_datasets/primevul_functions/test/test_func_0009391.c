static void rsi_set_default_parameters(struct rsi_common *common)
{
	common->band = NL80211_BAND_2GHZ;
	common->channel_width = BW_20MHZ;
	common->rts_threshold = IEEE80211_MAX_RTS_THRESHOLD;
	common->channel = 1;
	common->min_rate = 0xffff;
	common->fsm_state = FSM_CARD_NOT_READY;
	common->iface_down = true;
	common->endpoint = EP_2GHZ_20MHZ;
	common->driver_mode = 1;
	common->lp_ps_handshake_mode = 0;
	common->ulp_ps_handshake_mode = 2;
	common->rf_power_val = 0;
	common->wlan_rf_power_mode = 0;
	common->obm_ant_sel_val = 2;
	common->beacon_interval = RSI_BEACON_INTERVAL;
	common->dtim_cnt = RSI_DTIM_COUNT;
	common->w9116_features.pll_mode = 0x0;
	common->w9116_features.rf_type = 1;
	common->w9116_features.wireless_mode = 0;
	common->w9116_features.enable_ppe = 0;
	common->w9116_features.afe_type = 1;
	common->w9116_features.dpd = 0;
	common->w9116_features.sifs_tx_enable = 0;
	common->w9116_features.ps_options = 0;
}

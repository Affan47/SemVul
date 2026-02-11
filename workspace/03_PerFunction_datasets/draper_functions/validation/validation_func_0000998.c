il3945_rs_rate_init(struct il_priv *il, struct ieee80211_sta *sta, u8 sta_id)
{
	struct ieee80211_hw *hw = il->hw;
	struct ieee80211_conf *conf = &il->hw->conf;
	struct il3945_sta_priv *psta;
	struct il3945_rs_sta *rs_sta;
	struct ieee80211_supported_band *sband;
	int i;

	D_INFO("enter\n");
	if (sta_id == il->hw_params.bcast_id)
		goto out;

	psta = (struct il3945_sta_priv *)sta->drv_priv;
	rs_sta = &psta->rs_sta;
	sband = hw->wiphy->bands[conf->chandef.chan->band];

	rs_sta->il = il;

	rs_sta->start_rate = RATE_INVALID;


	rs_sta->expected_tpt = il3945_expected_tpt_b;

	rs_sta->last_partial_flush = jiffies;
	rs_sta->last_flush = jiffies;
	rs_sta->flush_time = RATE_FLUSH;
	rs_sta->last_tx_packets = 0;

	rs_sta->rate_scale_flush.data = (unsigned long)rs_sta;
	rs_sta->rate_scale_flush.function = il3945_bg_rate_scale_flush;

	for (i = 0; i < RATE_COUNT_3945; i++)
		il3945_clear_win(&rs_sta->win[i]);


	for (i = sband->n_bitrates - 1; i >= 0; i--) {
		if (sta->supp_rates[sband->band] & (1 << i)) {
			rs_sta->last_txrate_idx = i;
			break;
		}
	}

	il->_3945.sta_supp_rates = sta->supp_rates[sband->band];

	if (sband->band == IEEE80211_BAND_5GHZ) {
		rs_sta->last_txrate_idx += IL_FIRST_OFDM_RATE;
		il->_3945.sta_supp_rates <<= IL_FIRST_OFDM_RATE;
	}

out:
	il->stations[sta_id].used &= ~IL_STA_UCODE_INPROGRESS;

	D_INFO("leave\n");
}

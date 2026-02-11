ar5523_create_rateset(struct ar5523 *ar,
				  struct ieee80211_bss_conf *bss_conf,
				  struct ar5523_cmd_rateset *rs,
				  bool basic)
{
	struct ieee80211_supported_band *band;
	struct ieee80211_sta *sta;
	int bit, i = 0;
	u32 sta_rate_set, basic_rate_set;

	sta = ieee80211_find_sta(ar->vif, bss_conf->bssid);
	basic_rate_set = bss_conf->basic_rates;
	if (!sta) {
		ar5523_info(ar, "STA not found. Cannot set rates\n");
		sta_rate_set = bss_conf->basic_rates;
	} else
		sta_rate_set = sta->supp_rates[ar->hw->conf.chandef.chan->band];

	ar5523_dbg(ar, "sta rate_set = %08x\n", sta_rate_set);

	band = ar->hw->wiphy->bands[ar->hw->conf.chandef.chan->band];
	for (bit = 0; bit < band->n_bitrates; bit++) {
		BUG_ON(i >= AR5523_MAX_NRATES);
		ar5523_dbg(ar, "Considering rate %d : %d\n",
			   band->bitrates[bit].hw_value, sta_rate_set & 1);
		if (sta_rate_set & 1) {
			rs->set[i] = band->bitrates[bit].hw_value;
			if (basic_rate_set & 1 && basic)
				rs->set[i] |= 0x80;
			i++;
		}
		sta_rate_set >>= 1;
		basic_rate_set >>= 1;
	}

	rs->length = i;
}

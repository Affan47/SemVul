rsi_mac80211_attach(struct rsi_common *common)
{
	int status = 0;
	struct ieee80211_hw *hw = NULL;
	struct wiphy *wiphy = NULL;
	struct rsi_hw *adapter = common->priv;
	u8 addr_mask[ETH_ALEN] = {0x0, 0x0, 0x0, 0x0, 0x0, 0x3};

	rsi_dbg(INIT_ZONE, "%s: Performing mac80211 attach\n", __func__);

	hw = ieee80211_alloc_hw(sizeof(struct rsi_hw), &mac80211_ops);
	if (!hw) {
		rsi_dbg(ERR_ZONE, "%s: ieee80211 hw alloc failed\n", __func__);
		return -ENOMEM;
	}

	wiphy = hw->wiphy;

	SET_IEEE80211_DEV(hw, adapter->device);

	hw->priv = adapter;
	adapter->hw = hw;

	ieee80211_hw_set(hw, SIGNAL_DBM);
	ieee80211_hw_set(hw, HAS_RATE_CONTROL);
	ieee80211_hw_set(hw, AMPDU_AGGREGATION);

	hw->queues = MAX_HW_QUEUES;
	hw->extra_tx_headroom = RSI_NEEDED_HEADROOM;

	hw->max_rates = 1;
	hw->max_rate_tries = MAX_RETRIES;

	hw->max_tx_aggregation_subframes = 6;
	rsi_register_rates_channels(adapter, IEEE80211_BAND_2GHZ);
	rsi_register_rates_channels(adapter, IEEE80211_BAND_5GHZ);
	hw->rate_control_algorithm = "AARF";

	SET_IEEE80211_PERM_ADDR(hw, common->mac_addr);
	ether_addr_copy(hw->wiphy->addr_mask, addr_mask);

	wiphy->interface_modes = BIT(NL80211_IFTYPE_STATION);
	wiphy->signal_type = CFG80211_SIGNAL_TYPE_MBM;
	wiphy->retry_short = RETRY_SHORT;
	wiphy->retry_long  = RETRY_LONG;
	wiphy->frag_threshold = IEEE80211_MAX_FRAG_THRESHOLD;
	wiphy->rts_threshold = IEEE80211_MAX_RTS_THRESHOLD;
	wiphy->flags = 0;

	wiphy->available_antennas_rx = 1;
	wiphy->available_antennas_tx = 1;
	wiphy->bands[IEEE80211_BAND_2GHZ] =
		&adapter->sbands[IEEE80211_BAND_2GHZ];
	wiphy->bands[IEEE80211_BAND_5GHZ] =
		&adapter->sbands[IEEE80211_BAND_5GHZ];

	status = ieee80211_register_hw(hw);
	if (status)
		return status;

	return rsi_init_dbgfs(adapter);
}

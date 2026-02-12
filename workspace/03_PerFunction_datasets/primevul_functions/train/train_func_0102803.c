ieee80211_rx_h_userspace_mgmt(struct ieee80211_rx_data *rx)
{
	struct ieee80211_rx_status *status = IEEE80211_SKB_RXCB(rx->skb);
	int sig = 0;


	if (status->rx_flags & IEEE80211_RX_MALFORMED_ACTION_FRM)
		return RX_CONTINUE;


	if (ieee80211_hw_check(&rx->local->hw, SIGNAL_DBM) &&
	    !(status->flag & RX_FLAG_NO_SIGNAL_VAL))
		sig = status->signal;

	if (cfg80211_rx_mgmt(&rx->sdata->wdev, status->freq, sig,
			     rx->skb->data, rx->skb->len, 0)) {
		if (rx->sta)
			rx->sta->rx_stats.packets++;
		dev_kfree_skb(rx->skb);
		return RX_QUEUED;
	}

	return RX_CONTINUE;
}

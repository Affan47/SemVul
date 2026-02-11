wl1271_tx_reset_link_queues(struct wl1271 *wl, u8 hlid)
{
	struct sk_buff *skb;
	int i;
	unsigned long flags;
	struct ieee80211_tx_info *info;
	int total[NUM_TX_QUEUES];
	struct wl1271_link *lnk = &wl->links[hlid];

	for (i = 0; i < NUM_TX_QUEUES; i++) {
		total[i] = 0;
		while ((skb = skb_dequeue(&lnk->tx_queue[i]))) {
			wl1271_debug(DEBUG_TX, "link freeing skb 0x%p", skb);

			if (!wl12xx_is_dummy_packet(wl, skb)) {
				info = IEEE80211_SKB_CB(skb);
				info->status.rates[0].idx = -1;
				info->status.rates[0].count = 0;
				ieee80211_tx_status_ni(wl->hw, skb);
			}

			total[i]++;
		}
	}

	spin_lock_irqsave(&wl->wl_lock, flags);
	for (i = 0; i < NUM_TX_QUEUES; i++) {
		wl->tx_queue_count[i] -= total[i];
		if (lnk->wlvif)
			lnk->wlvif->tx_queue_count[i] -= total[i];
	}
	spin_unlock_irqrestore(&wl->wl_lock, flags);

	wl1271_handle_tx_low_watermark(wl);
}

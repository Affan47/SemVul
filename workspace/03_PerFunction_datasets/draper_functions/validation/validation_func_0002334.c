at76_hw_scan(struct ieee80211_hw *hw,
			struct ieee80211_vif *vif,
			struct ieee80211_scan_request *hw_req)
{
	struct cfg80211_scan_request *req = &hw_req->req;
	struct at76_priv *priv = hw->priv;
	struct at76_req_scan scan;
	u8 *ssid = NULL;
	int ret, len = 0;

	at76_dbg(DBG_MAC80211, "%s():", __func__);

	if (priv->device_unplugged)
		return 0;

	mutex_lock(&priv->mtx);

	ieee80211_stop_queues(hw);

	memset(&scan, 0, sizeof(struct at76_req_scan));
	eth_broadcast_addr(scan.bssid);

	if (req->n_ssids) {
		scan.scan_type = SCAN_TYPE_ACTIVE;
		ssid = req->ssids[0].ssid;
		len = req->ssids[0].ssid_len;
	} else {
		scan.scan_type = SCAN_TYPE_PASSIVE;
	}

	if (len) {
		memcpy(scan.essid, ssid, len);
		scan.essid_size = len;
	}

	scan.min_channel_time = cpu_to_le16(priv->scan_min_time);
	scan.max_channel_time = cpu_to_le16(priv->scan_max_time);
	scan.probe_delay = cpu_to_le16(priv->scan_min_time * 1000);
	scan.international_scan = 0;

	at76_dbg(DBG_MAC80211, "%s: sending CMD_SCAN", __func__);
	ret = at76_set_card_command(priv->udev, CMD_SCAN, &scan, sizeof(scan));

	if (ret < 0) {
		wiphy_err(priv->hw->wiphy, "CMD_SCAN failed: %d\n", ret);
		goto exit;
	}

	priv->scanning = true;
	ieee80211_queue_delayed_work(priv->hw, &priv->dwork_hw_scan,
				     SCAN_POLL_INTERVAL);

exit:
	mutex_unlock(&priv->mtx);

	return 0;
}

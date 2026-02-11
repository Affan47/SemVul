b43legacy_wireless_init(struct ssb_device *dev)
{
	struct ssb_sprom *sprom = &dev->bus->sprom;
	struct ieee80211_hw *hw;
	struct b43legacy_wl *wl;
	int err = -ENOMEM;
	int queue_num;

	b43legacy_sprom_fixup(dev->bus);

	hw = ieee80211_alloc_hw(sizeof(*wl), &b43legacy_hw_ops);
	if (!hw) {
		b43legacyerr(NULL, "Could not allocate ieee80211 device\n");
		goto out;
	}


	ieee80211_hw_set(hw, RX_INCLUDES_FCS);
	ieee80211_hw_set(hw, SIGNAL_DBM);

	hw->wiphy->interface_modes =
		BIT(NL80211_IFTYPE_AP) |
		BIT(NL80211_IFTYPE_STATION) |
		BIT(NL80211_IFTYPE_WDS) |
		BIT(NL80211_IFTYPE_ADHOC);
	hw->queues = 1;
	hw->max_rates = 2;
	SET_IEEE80211_DEV(hw, dev->dev);
	if (is_valid_ether_addr(sprom->et1mac))
		SET_IEEE80211_PERM_ADDR(hw, sprom->et1mac);
	else
		SET_IEEE80211_PERM_ADDR(hw, sprom->il0mac);


	wl = hw_to_b43legacy_wl(hw);
	memset(wl, 0, sizeof(*wl));
	wl->hw = hw;
	spin_lock_init(&wl->irq_lock);
	spin_lock_init(&wl->leds_lock);
	mutex_init(&wl->mutex);
	INIT_LIST_HEAD(&wl->devlist);
	INIT_WORK(&wl->beacon_update_trigger, b43legacy_beacon_update_trigger_work);
	INIT_WORK(&wl->tx_work, b43legacy_tx_work);


	for (queue_num = 0; queue_num < B43legacy_QOS_QUEUE_NUM; queue_num++) {
		skb_queue_head_init(&wl->tx_queue[queue_num]);
		wl->tx_queue_stopped[queue_num] = 0;
	}

	ssb_set_devtypedata(dev, wl);
	b43legacyinfo(wl, "Broadcom %04X WLAN found (core revision %u)\n",
		      dev->bus->chip_id, dev->id.revision);
	err = 0;
out:
	return err;
}

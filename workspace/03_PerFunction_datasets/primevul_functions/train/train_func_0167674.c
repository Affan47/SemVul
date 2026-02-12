static void b43_update_templates(struct b43_wl *wl)
{
	struct sk_buff *beacon;


	beacon = ieee80211_beacon_get(wl->hw, wl->vif);
	if (unlikely(!beacon))
		return;

	if (wl->current_beacon)
		dev_kfree_skb_any(wl->current_beacon);
	wl->current_beacon = beacon;
	wl->beacon0_uploaded = false;
	wl->beacon1_uploaded = false;
	ieee80211_queue_work(wl->hw, &wl->beacon_update_trigger);
}

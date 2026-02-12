void ieee80211_sta_uapsd_trigger(struct ieee80211_sta *pubsta, u8 tid)
{
	struct sta_info *sta = container_of(pubsta, struct sta_info, sta);
	int ac = ieee80211_ac_from_tid(tid);


	if (!(sta->sta.uapsd_queues & ieee80211_ac_to_qos_mask[ac]) &&
	    tid != IEEE80211_NUM_TIDS)
		return;


	if (test_sta_flag(sta, WLAN_STA_SP))
		return;

	if (!test_sta_flag(sta, WLAN_STA_PS_DRIVER))
		ieee80211_sta_ps_deliver_uapsd(sta);
	else
		set_sta_flag(sta, WLAN_STA_UAPSD);
}

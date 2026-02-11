rtl_beacon_statistic(struct ieee80211_hw *hw, struct sk_buff *skb)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct ieee80211_hdr *hdr = (struct ieee80211_hdr *)skb->data;

	if (rtlpriv->mac80211.opmode != NL80211_IFTYPE_STATION)
		return;

	if (rtlpriv->mac80211.link_state < MAC80211_LINKED)
		return;


	if (!ieee80211_is_beacon(hdr->frame_control) &&
	    !ieee80211_is_probe_resp(hdr->frame_control))
		return;


	if (skb->len <= 40 + FCS_LEN)
		return;


	if (!ether_addr_equal(hdr->addr3, rtlpriv->mac80211.bssid))
		return;

	rtlpriv->link_info.bcn_rx_inperiod++;
}

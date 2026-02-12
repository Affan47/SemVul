static void rtl_lps_enter_core(struct ieee80211_hw *hw)
{
	struct rtl_mac *mac = rtl_mac(rtl_priv(hw));
	struct rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));
	struct rtl_priv *rtlpriv = rtl_priv(hw);

	if (!ppsc->fwctrl_lps)
		return;

	if (rtlpriv->sec.being_setkey)
		return;

	if (rtlpriv->link_info.busytraffic)
		return;


	if (mac->cnt_after_linked < 5)
		return;

	if (mac->opmode == NL80211_IFTYPE_ADHOC)
		return;

	if (mac->link_state != MAC80211_LINKED)
		return;

	mutex_lock(&rtlpriv->locks.lps_mutex);


	RT_TRACE(rtlpriv, COMP_POWER, DBG_LOUD,
		 "Enter 802.11 power save mode...\n");
	rtl_lps_set_psmode(hw, EAUTOPS);

	mutex_unlock(&rtlpriv->locks.lps_mutex);
}

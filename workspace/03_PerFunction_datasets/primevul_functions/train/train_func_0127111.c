void rtl_ips_nic_off_wq_callback(void *data)
{
	struct rtl_works *rtlworks =
	    container_of_dwork_rtl(data, struct rtl_works, ips_nic_off_wq);
	struct ieee80211_hw *hw = rtlworks->hw;
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	struct rtl_mac *mac = rtl_mac(rtl_priv(hw));
	struct rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));
	enum rf_pwrstate rtstate;

	if (mac->opmode != NL80211_IFTYPE_STATION) {
		RT_TRACE(rtlpriv, COMP_ERR, DBG_WARNING,
			 "not station return\n");
		return;
	}

	if (mac->p2p_in_use)
		return;

	if (mac->link_state > MAC80211_NOLINK)
		return;

	if (is_hal_stop(rtlhal))
		return;

	if (rtlpriv->sec.being_setkey)
		return;

	if (rtlpriv->cfg->ops->bt_coex_off_before_lps)
		rtlpriv->cfg->ops->bt_coex_off_before_lps(hw);

	if (ppsc->inactiveps) {
		rtstate = ppsc->rfpwr_state;


		if (rtstate == ERFON &&
		    !ppsc->swrf_processing &&
		    (mac->link_state == MAC80211_NOLINK) &&
		    !mac->act_scanning) {
			RT_TRACE(rtlpriv, COMP_RF, DBG_TRACE,
				 "IPSEnter(): Turn off RF\n");

			ppsc->inactive_pwrstate = ERFOFF;
			ppsc->in_powersavemode = true;


			if (rtlpriv->cfg->ops->get_btc_status())
				rtlpriv->btcoexist.btc_ops->btc_ips_notify(rtlpriv,
									ppsc->inactive_pwrstate);


			_rtl_ps_inactive_ps(hw);
		}
	}
}

bool rtl_ps_disable_nic(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);


	rtl_deinit_deferred_work(hw, true);


	rtlpriv->cfg->ops->disable_interrupt(hw);
	tasklet_kill(&rtlpriv->works.irq_tasklet);


	rtlpriv->cfg->ops->hw_disable(hw);

	return true;
}

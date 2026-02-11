at76_configure_filter(struct ieee80211_hw *hw,
				  unsigned int changed_flags,
				  unsigned int *total_flags, u64 multicast)
{
	struct at76_priv *priv = hw->priv;
	int flags;

	at76_dbg(DBG_MAC80211, "%s(): changed_flags=0x%08x "
		 "total_flags=0x%08x",
		 __func__, changed_flags, *total_flags);

	flags = changed_flags & AT76_SUPPORTED_FILTERS;
	*total_flags = AT76_SUPPORTED_FILTERS;


	if (priv->device_unplugged)
		return;


	if (flags && !priv->promisc) {

		priv->promisc = 1;
	} else if (!flags && priv->promisc) {

		priv->promisc = 0;
	} else
		return;

	ieee80211_queue_work(hw, &priv->work_set_promisc);
}

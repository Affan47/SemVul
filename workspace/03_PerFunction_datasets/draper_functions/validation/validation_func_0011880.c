__cw1200_sta_notify(struct ieee80211_hw *dev,
				struct ieee80211_vif *vif,
				enum sta_notify_cmd notify_cmd,
				int link_id)
{
	struct cw1200_common *priv = dev->priv;
	u32 bit, prev;


	if (link_id)
		bit = BIT(link_id);
	else if (WARN_ON_ONCE(notify_cmd != STA_NOTIFY_AWAKE))
		bit = 0;
	else
		bit = priv->link_id_map;
	prev = priv->sta_asleep_mask & bit;

	switch (notify_cmd) {
	case STA_NOTIFY_SLEEP:
		if (!prev) {
			if (priv->buffered_multicasts &&
			    !priv->sta_asleep_mask)
				queue_work(priv->workqueue,
					   &priv->multicast_start_work);
			priv->sta_asleep_mask |= bit;
		}
		break;
	case STA_NOTIFY_AWAKE:
		if (prev) {
			priv->sta_asleep_mask &= ~bit;
			priv->pspoll_mask &= ~bit;
			if (priv->tx_multicast && link_id &&
			    !priv->sta_asleep_mask)
				queue_work(priv->workqueue,
					   &priv->multicast_stop_work);
			cw1200_bh_wakeup(priv);
		}
		break;
	}
}

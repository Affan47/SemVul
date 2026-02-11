cw1200_set_tim_impl(struct cw1200_common *priv, bool aid0_bit_set)
{
	struct sk_buff *skb;
	struct wsm_update_ie update_ie = {
		.what = WSM_UPDATE_IE_BEACON,
		.count = 1,
	};
	u16 tim_offset, tim_length;

	pr_debug("[AP] mcast: %s.\n", aid0_bit_set ? "ena" : "dis");

	skb = ieee80211_beacon_get_tim(priv->hw, priv->vif,
			&tim_offset, &tim_length);
	if (!skb) {
		if (!__cw1200_flush(priv, true))
			wsm_unlock_tx(priv);
		return -ENOENT;
	}

	if (tim_offset && tim_length >= 6) {


		skb->data[tim_offset + 2] = 0;


		if (aid0_bit_set)
			skb->data[tim_offset + 4] |= 1;
		else
			skb->data[tim_offset + 4] &= ~1;
	}

	update_ie.ies = &skb->data[tim_offset];
	update_ie.length = tim_length;
	wsm_update_ie(priv, &update_ie);

	dev_kfree_skb(skb);

	return 0;
}

ieee80211_rx_monitor(struct ieee80211_local *local, struct sk_buff *origskb,
		     struct ieee80211_rate *rate)
{
	struct ieee80211_rx_status *status = IEEE80211_SKB_RXCB(origskb);
	struct ieee80211_sub_if_data *sdata;
	struct sk_buff *monskb = NULL;
	int present_fcs_len = 0;
	unsigned int rtap_space = 0;
	struct ieee80211_sub_if_data *monitor_sdata =
		rcu_dereference(local->monitor_sdata);
	bool only_monitor = false;
	unsigned int min_head_len;

	if (status->flag & RX_FLAG_RADIOTAP_HE)
		rtap_space += sizeof(struct ieee80211_radiotap_he);

	if (status->flag & RX_FLAG_RADIOTAP_HE_MU)
		rtap_space += sizeof(struct ieee80211_radiotap_he_mu);

	if (status->flag & RX_FLAG_RADIOTAP_LSIG)
		rtap_space += sizeof(struct ieee80211_radiotap_lsig);

	if (unlikely(status->flag & RX_FLAG_RADIOTAP_VENDOR_DATA)) {
		struct ieee80211_vendor_radiotap *rtap =
			(void *)(origskb->data + rtap_space);

		rtap_space += sizeof(*rtap) + rtap->len + rtap->pad;
	}

	min_head_len = rtap_space;


	if (!(status->flag & RX_FLAG_NO_PSDU)) {
		if (ieee80211_hw_check(&local->hw, RX_INCLUDES_FCS)) {
			if (unlikely(origskb->len <= FCS_LEN + rtap_space)) {

				WARN_ON(1);
				dev_kfree_skb(origskb);
				return NULL;
			}
			present_fcs_len = FCS_LEN;
		}


		min_head_len += 2;
	}


	if (!pskb_may_pull(origskb, min_head_len)) {
		dev_kfree_skb(origskb);
		return NULL;
	}

	only_monitor = should_drop_frame(origskb, present_fcs_len, rtap_space);

	if (!local->monitors || (status->flag & RX_FLAG_SKIP_MONITOR)) {
		if (only_monitor) {
			dev_kfree_skb(origskb);
			return NULL;
		}

		remove_monitor_info(origskb, present_fcs_len, rtap_space);
		return origskb;
	}

	ieee80211_handle_mu_mimo_mon(monitor_sdata, origskb, rtap_space);

	list_for_each_entry_rcu(sdata, &local->mon_list, u.mntr.list) {
		bool last_monitor = list_is_last(&sdata->u.mntr.list,
						 &local->mon_list);

		if (!monskb)
			monskb = ieee80211_make_monitor_skb(local, &origskb,
							    rate, rtap_space,
							    only_monitor &&
							    last_monitor);

		if (monskb) {
			struct sk_buff *skb;

			if (last_monitor) {
				skb = monskb;
				monskb = NULL;
			} else {
				skb = skb_clone(monskb, GFP_ATOMIC);
			}

			if (skb) {
				skb->dev = sdata->dev;
				ieee80211_rx_stats(skb->dev, skb->len);
				netif_receive_skb(skb);
			}
		}

		if (last_monitor)
			break;
	}


	dev_kfree_skb(monskb);


	if (!origskb)
		return NULL;

	remove_monitor_info(origskb, present_fcs_len, rtap_space);
	return origskb;
}

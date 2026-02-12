int ip_mr_input(struct sk_buff *skb)
{
	struct mfc_cache *cache;
	int local = ((struct rtable*)skb->dst)->rt_flags&RTCF_LOCAL;


	if (IPCB(skb)->flags&IPSKB_FORWARDED)
		goto dont_forward;

	if (!local) {
		    if (IPCB(skb)->opt.router_alert) {
			    if (ip_call_ra_chain(skb))
				    return 0;
		    } else if (skb->nh.iph->protocol == IPPROTO_IGMP){


			    read_lock(&mrt_lock);
			    if (mroute_socket) {
				    nf_reset(skb);
				    raw_rcv(mroute_socket, skb);
				    read_unlock(&mrt_lock);
				    return 0;
			    }
			    read_unlock(&mrt_lock);
		    }
	}

	read_lock(&mrt_lock);
	cache = ipmr_cache_find(skb->nh.iph->saddr, skb->nh.iph->daddr);


	if (cache==NULL) {
		int vif;

		if (local) {
			struct sk_buff *skb2 = skb_clone(skb, GFP_ATOMIC);
			ip_local_deliver(skb);
			if (skb2 == NULL) {
				read_unlock(&mrt_lock);
				return -ENOBUFS;
			}
			skb = skb2;
		}

		vif = ipmr_find_vif(skb->dev);
		if (vif >= 0) {
			int err = ipmr_cache_unresolved(vif, skb);
			read_unlock(&mrt_lock);

			return err;
		}
		read_unlock(&mrt_lock);
		kfree_skb(skb);
		return -ENODEV;
	}

	ip_mr_forward(skb, cache, local);

	read_unlock(&mrt_lock);

	if (local)
		return ip_local_deliver(skb);

	return 0;

dont_forward:
	if (local)
		return ip_local_deliver(skb);
	kfree_skb(skb);
	return 0;
}

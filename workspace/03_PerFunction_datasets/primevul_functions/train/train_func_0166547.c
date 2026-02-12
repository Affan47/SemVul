static void ipmr_queue_xmit(struct sk_buff *skb, struct mfc_cache *c, int vifi)
{
	struct iphdr *iph = skb->nh.iph;
	struct vif_device *vif = &vif_table[vifi];
	struct net_device *dev;
	struct rtable *rt;
	int    encap = 0;

	if (vif->dev == NULL)
		goto out_free;

#ifdef CONFIG_IP_PIMSM
	if (vif->flags & VIFF_REGISTER) {
		vif->pkt_out++;
		vif->bytes_out+=skb->len;
		((struct net_device_stats*)vif->dev->priv)->tx_bytes += skb->len;
		((struct net_device_stats*)vif->dev->priv)->tx_packets++;
		ipmr_cache_report(skb, vifi, IGMPMSG_WHOLEPKT);
		kfree_skb(skb);
		return;
	}
#endif

	if (vif->flags&VIFF_TUNNEL) {
		struct flowi fl = { .oif = vif->link,
				    .nl_u = { .ip4_u =
					      { .daddr = vif->remote,
						.saddr = vif->local,
						.tos = RT_TOS(iph->tos) } },
				    .proto = IPPROTO_IPIP };
		if (ip_route_output_key(&rt, &fl))
			goto out_free;
		encap = sizeof(struct iphdr);
	} else {
		struct flowi fl = { .oif = vif->link,
				    .nl_u = { .ip4_u =
					      { .daddr = iph->daddr,
						.tos = RT_TOS(iph->tos) } },
				    .proto = IPPROTO_IPIP };
		if (ip_route_output_key(&rt, &fl))
			goto out_free;
	}

	dev = rt->u.dst.dev;

	if (skb->len+encap > dst_mtu(&rt->u.dst) && (ntohs(iph->frag_off) & IP_DF)) {


		IP_INC_STATS_BH(IPSTATS_MIB_FRAGFAILS);
		ip_rt_put(rt);
		goto out_free;
	}

	encap += LL_RESERVED_SPACE(dev) + rt->u.dst.header_len;

	if (skb_cow(skb, encap)) {
 		ip_rt_put(rt);
		goto out_free;
	}

	vif->pkt_out++;
	vif->bytes_out+=skb->len;

	dst_release(skb->dst);
	skb->dst = &rt->u.dst;
	iph = skb->nh.iph;
	ip_decrease_ttl(iph);


	if (vif->flags & VIFF_TUNNEL) {
		ip_encap(skb, vif->local, vif->remote);

		((struct ip_tunnel *)vif->dev->priv)->stat.tx_packets++;
		((struct ip_tunnel *)vif->dev->priv)->stat.tx_bytes+=skb->len;
	}

	IPCB(skb)->flags |= IPSKB_FORWARDED;


	NF_HOOK(PF_INET, NF_IP_FORWARD, skb, skb->dev, dev,
		ipmr_forward_finish);
	return;

out_free:
	kfree_skb(skb);
	return;
}

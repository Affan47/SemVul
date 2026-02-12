static u32 netif_receive_generic_xdp(struct sk_buff *skb,
				     struct xdp_buff *xdp,
				     struct bpf_prog *xdp_prog)
{
	struct netdev_rx_queue *rxqueue;
	void *orig_data, *orig_data_end;
	u32 metalen, act = XDP_DROP;
	__be16 orig_eth_type;
	struct ethhdr *eth;
	bool orig_bcast;
	int hlen, off;
	u32 mac_len;


	if (skb_cloned(skb) || skb_is_tc_redirected(skb))
		return XDP_PASS;


	if (skb_is_nonlinear(skb) ||
	    skb_headroom(skb) < XDP_PACKET_HEADROOM) {
		int hroom = XDP_PACKET_HEADROOM - skb_headroom(skb);
		int troom = skb->tail + skb->data_len - skb->end;


		if (pskb_expand_head(skb,
				     hroom > 0 ? ALIGN(hroom, NET_SKB_PAD) : 0,
				     troom > 0 ? troom + 128 : 0, GFP_ATOMIC))
			goto do_drop;
		if (skb_linearize(skb))
			goto do_drop;
	}


	mac_len = skb->data - skb_mac_header(skb);
	hlen = skb_headlen(skb) + mac_len;
	xdp->data = skb->data - mac_len;
	xdp->data_meta = xdp->data;
	xdp->data_end = xdp->data + hlen;
	xdp->data_hard_start = skb->data - skb_headroom(skb);
	orig_data_end = xdp->data_end;
	orig_data = xdp->data;
	eth = (struct ethhdr *)xdp->data;
	orig_bcast = is_multicast_ether_addr_64bits(eth->h_dest);
	orig_eth_type = eth->h_proto;

	rxqueue = netif_get_rxqueue(skb);
	xdp->rxq = &rxqueue->xdp_rxq;

	act = bpf_prog_run_xdp(xdp_prog, xdp);

	off = xdp->data - orig_data;
	if (off > 0)
		__skb_pull(skb, off);
	else if (off < 0)
		__skb_push(skb, -off);
	skb->mac_header += off;


	off = orig_data_end - xdp->data_end;
	if (off != 0) {
		skb_set_tail_pointer(skb, xdp->data_end - xdp->data);
		skb->len -= off;

	}


	eth = (struct ethhdr *)xdp->data;
	if ((orig_eth_type != eth->h_proto) ||
	    (orig_bcast != is_multicast_ether_addr_64bits(eth->h_dest))) {
		__skb_push(skb, ETH_HLEN);
		skb->protocol = eth_type_trans(skb, skb->dev);
	}

	switch (act) {
	case XDP_REDIRECT:
	case XDP_TX:
		__skb_push(skb, mac_len);
		break;
	case XDP_PASS:
		metalen = xdp->data - xdp->data_meta;
		if (metalen)
			skb_metadata_set(skb, metalen);
		break;
	default:
		bpf_warn_invalid_xdp_action(act);

	case XDP_ABORTED:
		trace_xdp_exception(skb->dev, xdp_prog, act);

	case XDP_DROP:
	do_drop:
		kfree_skb(skb);
		break;
	}

	return act;
}

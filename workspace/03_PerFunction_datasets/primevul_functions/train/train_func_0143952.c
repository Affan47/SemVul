isdn_net_type_trans(struct sk_buff *skb, struct net_device *dev)
{
	struct ethhdr *eth;
	unsigned char *rawp;

	skb_reset_mac_header(skb);
	skb_pull(skb, ETH_HLEN);
	eth = eth_hdr(skb);

	if (*eth->h_dest & 1) {
		if (ether_addr_equal(eth->h_dest, dev->broadcast))
			skb->pkt_type = PACKET_BROADCAST;
		else
			skb->pkt_type = PACKET_MULTICAST;
	}


	else if (dev->flags & (IFF_PROMISC )) {
		if (!ether_addr_equal(eth->h_dest, dev->dev_addr))
			skb->pkt_type = PACKET_OTHERHOST;
	}
	if (ntohs(eth->h_proto) >= ETH_P_802_3_MIN)
		return eth->h_proto;

	rawp = skb->data;


	if (*(unsigned short *) rawp == 0xFFFF)
		return htons(ETH_P_802_3);


	return htons(ETH_P_802_2);
}

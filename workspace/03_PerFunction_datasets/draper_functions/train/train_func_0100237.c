rx(struct net_device *dev, int bufnum,
	       struct archdr *pkthdr, int length)
{
	struct arcnet_local *lp = netdev_priv(dev);
	struct sk_buff *skb;
	struct archdr *pkt = pkthdr;
	int ofs;

	arc_printk(D_DURING, dev, "it's a raw packet (length=%d)\n", length);

	if (length > MTU)
		ofs = 512 - length;
	else
		ofs = 256 - length;

	skb = alloc_skb(length + ARC_HDR_SIZE, GFP_ATOMIC);
	if (!skb) {
		dev->stats.rx_dropped++;
		return;
	}
	skb_put(skb, length + ARC_HDR_SIZE);
	skb->dev = dev;

	pkt = (struct archdr *)skb->data;

	skb_reset_mac_header(skb);
	skb_pull(skb, ARC_HDR_SIZE);


	memcpy(pkt, pkthdr, sizeof(struct archdr));
	if (length > sizeof(pkt->soft))
		lp->hw.copy_from_card(dev, bufnum, ofs + sizeof(pkt->soft),
				      pkt->soft.raw + sizeof(pkt->soft),
				      length - sizeof(pkt->soft));

	if (BUGLVL(D_SKB))
		arcnet_dump_skb(dev, skb, "rx");

	skb->protocol = cpu_to_be16(ETH_P_ARCNET);
	netif_rx(skb);
}

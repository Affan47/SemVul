aoenet_rcv(struct sk_buff *skb, struct net_device *ifp, struct packet_type *pt, struct net_device *orig_dev)
{
	struct aoe_hdr *h;
	struct aoe_atahdr *ah;
	u32 n;
	int sn;

	if (dev_net(ifp) != &init_net)
		goto exit;

	skb = skb_share_check(skb, GFP_ATOMIC);
	if (skb == NULL)
		return 0;
	if (!is_aoe_netif(ifp))
		goto exit;
	skb_push(skb, ETH_HLEN);
	sn = sizeof(*h) + sizeof(*ah);
	if (skb->len >= sn) {
		sn -= skb_headlen(skb);
		if (sn > 0 && !__pskb_pull_tail(skb, sn))
			goto exit;
	}
	h = (struct aoe_hdr *) skb->data;
	n = get_unaligned_be32(&h->tag);
	if ((h->verfl & AOEFL_RSP) == 0 || (n & 1<<31))
		goto exit;

	if (h->verfl & AOEFL_ERR) {
		n = h->err;
		if (n > NECODES)
			n = 0;
		if (net_ratelimit())
			printk(KERN_ERR
				"%s%d.%d@%s; ecode=%d '%s'\n",
				"aoe: error packet from ",
				get_unaligned_be16(&h->major),
				h->minor, skb->dev->name,
				h->err, aoe_errlist[n]);
		goto exit;
	}

	switch (h->cmd) {
	case AOECMD_ATA:

		skb = aoecmd_ata_rsp(skb);
		break;
	case AOECMD_CFG:
		aoecmd_cfg_rsp(skb);
		break;
	default:
		if (h->cmd >= AOECMD_VEND_MIN)
			break;
		pr_info("aoe: unknown AoE command type 0x%02x\n", h->cmd);
		break;
	}

	if (!skb)
		return 0;
exit:
	dev_kfree_skb(skb);
	return 0;
}

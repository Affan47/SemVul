nfqnl_enqueue_packet(struct nf_queue_entry *entry, unsigned int queuenum)
{
	unsigned int queued;
	struct nfqnl_instance *queue;
	struct sk_buff *skb, *segs;
	int err = -ENOBUFS;
	struct net *net = dev_net(entry->indev ?
				  entry->indev : entry->outdev);
	struct nfnl_queue_net *q = nfnl_queue_pernet(net);


	queue = instance_lookup(q, queuenum);
	if (!queue)
		return -ESRCH;

	if (queue->copy_mode == NFQNL_COPY_NONE)
		return -EINVAL;

	skb = entry->skb;

	switch (entry->pf) {
	case NFPROTO_IPV4:
		skb->protocol = htons(ETH_P_IP);
		break;
	case NFPROTO_IPV6:
		skb->protocol = htons(ETH_P_IPV6);
		break;
	}

	if ((queue->flags & NFQA_CFG_F_GSO) || !skb_is_gso(skb))
		return __nfqnl_enqueue_packet(net, queue, entry);

	nf_bridge_adjust_skb_data(skb);
	segs = skb_gso_segment(skb, 0);


	if (IS_ERR(segs))
		goto out_err;
	queued = 0;
	err = 0;
	do {
		struct sk_buff *nskb = segs->next;
		if (err == 0)
			err = __nfqnl_enqueue_packet_gso(net, queue,
							segs, entry);
		if (err == 0)
			queued++;
		else
			kfree_skb(segs);
		segs = nskb;
	} while (segs);

	if (queued) {
		if (err)
			free_entry(entry);
		kfree_skb(skb);
		return 0;
	}
 out_err:
	nf_bridge_adjust_segmented_data(skb);
	return err;
}

static int ip_frag_queue(struct ipq *qp, struct sk_buff *skb)
{
	struct net *net = container_of(qp->q.net, struct net, ipv4.frags);
	struct rb_node **rbn, *parent;
	struct sk_buff *skb1, *prev_tail;
	struct net_device *dev;
	unsigned int fragsize;
	int flags, offset;
	int ihl, end;
	int err = -ENOENT;
	u8 ecn;

	if (qp->q.flags & INET_FRAG_COMPLETE)
		goto err;

	if (!(IPCB(skb)->flags & IPSKB_FRAG_COMPLETE) &&
	    unlikely(ip_frag_too_far(qp)) &&
	    unlikely(err = ip_frag_reinit(qp))) {
		ipq_kill(qp);
		goto err;
	}

	ecn = ip4_frag_ecn(ip_hdr(skb)->tos);
	offset = ntohs(ip_hdr(skb)->frag_off);
	flags = offset & ~IP_OFFSET;
	offset &= IP_OFFSET;
	offset <<= 3;
	ihl = ip_hdrlen(skb);


	end = offset + skb->len - skb_network_offset(skb) - ihl;
	err = -EINVAL;


	if ((flags & IP_MF) == 0) {


		if (end < qp->q.len ||
		    ((qp->q.flags & INET_FRAG_LAST_IN) && end != qp->q.len))
			goto err;
		qp->q.flags |= INET_FRAG_LAST_IN;
		qp->q.len = end;
	} else {
		if (end&7) {
			end &= ~7;
			if (skb->ip_summed != CHECKSUM_UNNECESSARY)
				skb->ip_summed = CHECKSUM_NONE;
		}
		if (end > qp->q.len) {

			if (qp->q.flags & INET_FRAG_LAST_IN)
				goto err;
			qp->q.len = end;
		}
	}
	if (end == offset)
		goto err;

	err = -ENOMEM;
	if (!pskb_pull(skb, skb_network_offset(skb) + ihl))
		goto err;

	err = pskb_trim_rcsum(skb, end - offset);
	if (err)
		goto err;


	dev = skb->dev;

	barrier();


	prev_tail = qp->q.fragments_tail;
	if (!prev_tail)
		ip4_frag_create_run(&qp->q, skb);
	else if (prev_tail->ip_defrag_offset + prev_tail->len < end) {


		if (offset < prev_tail->ip_defrag_offset + prev_tail->len)
			goto discard_qp;
		if (offset == prev_tail->ip_defrag_offset + prev_tail->len)
			ip4_frag_append_to_last_run(&qp->q, skb);
		else
			ip4_frag_create_run(&qp->q, skb);
	} else {


		rbn = &qp->q.rb_fragments.rb_node;
		do {
			parent = *rbn;
			skb1 = rb_to_skb(parent);
			if (end <= skb1->ip_defrag_offset)
				rbn = &parent->rb_left;
			else if (offset >= skb1->ip_defrag_offset +
						FRAG_CB(skb1)->frag_run_len)
				rbn = &parent->rb_right;
			else
				goto discard_qp;
		} while (*rbn);


		ip4_frag_init_run(skb);
		rb_link_node(&skb->rbnode, parent, rbn);
		rb_insert_color(&skb->rbnode, &qp->q.rb_fragments);
	}

	if (dev)
		qp->iif = dev->ifindex;
	skb->ip_defrag_offset = offset;

	qp->q.stamp = skb->tstamp;
	qp->q.meat += skb->len;
	qp->ecn |= ecn;
	add_frag_mem_limit(qp->q.net, skb->truesize);
	if (offset == 0)
		qp->q.flags |= INET_FRAG_FIRST_IN;

	fragsize = skb->len + ihl;

	if (fragsize > qp->q.max_size)
		qp->q.max_size = fragsize;

	if (ip_hdr(skb)->frag_off & htons(IP_DF) &&
	    fragsize > qp->max_df_size)
		qp->max_df_size = fragsize;

	if (qp->q.flags == (INET_FRAG_FIRST_IN | INET_FRAG_LAST_IN) &&
	    qp->q.meat == qp->q.len) {
		unsigned long orefdst = skb->_skb_refdst;

		skb->_skb_refdst = 0UL;
		err = ip_frag_reasm(qp, skb, prev_tail, dev);
		skb->_skb_refdst = orefdst;
		return err;
	}

	skb_dst_drop(skb);
	return -EINPROGRESS;

discard_qp:
	inet_frag_kill(&qp->q);
	err = -EINVAL;
	__IP_INC_STATS(net, IPSTATS_MIB_REASM_OVERLAPS);
err:
	kfree_skb(skb);
	return err;
}

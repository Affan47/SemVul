static void isdn_ppp_mp_receive(isdn_net_dev *net_dev, isdn_net_local *lp,
				struct sk_buff *skb)
{
	struct ippp_struct *is;
	isdn_net_local *lpq;
	ippp_bundle *mp;
	isdn_mppp_stats *stats;
	struct sk_buff *newfrag, *frag, *start, *nextf;
	u32 newseq, minseq, thisseq;
	unsigned long flags;
	int slot;

	spin_lock_irqsave(&net_dev->pb->lock, flags);
	mp = net_dev->pb;
	stats = &mp->stats;
	slot = lp->ppp_slot;
	if (slot < 0 || slot >= ISDN_MAX_CHANNELS) {
		printk(KERN_ERR "%s: lp->ppp_slot(%d)\n",
		       __func__, lp->ppp_slot);
		stats->frame_drops++;
		dev_kfree_skb(skb);
		spin_unlock_irqrestore(&mp->lock, flags);
		return;
	}
	is = ippp_table[slot];
	if (++mp->frames > stats->max_queue_len)
		stats->max_queue_len = mp->frames;

	if (is->debug & 0x8)
		isdn_ppp_mp_print_recv_pkt(lp->ppp_slot, skb);

	newseq = isdn_ppp_mp_get_seq(is->mpppcfg & SC_IN_SHORT_SEQ,
				     skb, is->last_link_seqno);


	if (mp->seq > MP_LONGSEQ_MAX && (newseq & MP_LONGSEQ_MAXBIT)) {
		mp->seq = newseq;


	} else if (MP_LT(newseq, mp->seq)) {
		stats->frame_drops++;
		isdn_ppp_mp_free_skb(mp, skb);
		spin_unlock_irqrestore(&mp->lock, flags);
		return;
	}


	is->last_link_seqno = minseq = newseq;
	for (lpq = net_dev->queue;;) {
		slot = lpq->ppp_slot;
		if (slot < 0 || slot >= ISDN_MAX_CHANNELS) {
			printk(KERN_ERR "%s: lpq->ppp_slot(%d)\n",
			       __func__, lpq->ppp_slot);
		} else {
			u32 lls = ippp_table[slot]->last_link_seqno;
			if (MP_LT(lls, minseq))
				minseq = lls;
		}
		if ((lpq = lpq->next) == net_dev->queue)
			break;
	}
	if (MP_LT(minseq, mp->seq))
		minseq = mp->seq;

	newfrag = skb;


	if ((frag = mp->frags) == NULL || MP_LT(newseq, MP_SEQ(frag))) {
		newfrag->next = frag;
		mp->frags = frag = newfrag;
		newfrag = NULL;
	}

	start = MP_FLAGS(frag) & MP_BEGIN_FRAG &&
		MP_SEQ(frag) == mp->seq ? frag : NULL;


	while (start != NULL || newfrag != NULL) {

		thisseq = MP_SEQ(frag);
		nextf = frag->next;


		if (newfrag != NULL && thisseq == newseq) {
			isdn_ppp_mp_free_skb(mp, newfrag);
			newfrag = NULL;
		}


		if (newfrag != NULL && (nextf == NULL ||
					MP_LT(newseq, MP_SEQ(nextf)))) {
			newfrag->next = nextf;
			frag->next = nextf = newfrag;
			newfrag = NULL;
		}

		if (start != NULL) {

			if (start != frag && (MP_FLAGS(frag) & MP_BEGIN_FRAG)) {
				printk(KERN_WARNING"isdn_mppp(seq %d): new "
				       "BEGIN flag with no prior END", thisseq);
				stats->seqerrs++;
				stats->frame_drops++;
				start = isdn_ppp_mp_discard(mp, start, frag);
				nextf = frag->next;
			}
		} else if (MP_LE(thisseq, minseq)) {
			if (MP_FLAGS(frag) & MP_BEGIN_FRAG)
				start = frag;
			else {
				if (MP_FLAGS(frag) & MP_END_FRAG)
					stats->frame_drops++;
				if (mp->frags == frag)
					mp->frags = nextf;
				isdn_ppp_mp_free_skb(mp, frag);
				frag = nextf;
				continue;
			}
		}


		if (start != NULL && (MP_FLAGS(frag) & MP_END_FRAG)) {
			minseq = mp->seq = (thisseq + 1) & MP_LONGSEQ_MASK;

			isdn_ppp_mp_reassembly(net_dev, lp, start, nextf);

			start = NULL;
			frag = NULL;

			mp->frags = nextf;
		}


		if (nextf != NULL &&
		    ((thisseq + 1) & MP_LONGSEQ_MASK) == MP_SEQ(nextf)) {


			if (frag == NULL) {
				if (MP_FLAGS(nextf) & MP_BEGIN_FRAG)
					start = nextf;
				else
				{
					printk(KERN_WARNING"isdn_mppp(seq %d):"
					       " END flag with no following "
					       "BEGIN", thisseq);
					stats->seqerrs++;
				}
			}

		} else {
			if (nextf != NULL && frag != NULL &&
			    MP_LT(thisseq, minseq)) {


				stats->frame_drops++;
				mp->frags = isdn_ppp_mp_discard(mp, start, nextf);
			}

			start = NULL;
		}

		frag = nextf;
	}

	if (mp->frags == NULL)
		mp->frags = frag;


	if (mp->frames > MP_MAX_QUEUE_LEN) {
		stats->overflows++;
		while (mp->frames > MP_MAX_QUEUE_LEN) {
			frag = mp->frags->next;
			isdn_ppp_mp_free_skb(mp, mp->frags);
			mp->frags = frag;
		}
	}
	spin_unlock_irqrestore(&mp->lock, flags);
}

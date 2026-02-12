static int ppp_mp_explode(struct ppp *ppp, struct sk_buff *skb)
{
	int len, fragsize;
	int i, bits, hdrlen, mtu;
	int flen;
	int navail, nfree;
	int nbigger;
	unsigned char *p, *q;
	struct list_head *list;
	struct channel *pch;
	struct sk_buff *frag;
	struct ppp_channel *chan;

	nfree = 0;
	navail = 0;
	hdrlen = (ppp->flags & SC_MP_XSHORTSEQ)? MPHDRLEN_SSN: MPHDRLEN;
	i = 0;
	list_for_each_entry(pch, &ppp->channels, clist) {
		navail += pch->avail = (pch->chan != NULL);
		if (pch->avail) {
			if (skb_queue_empty(&pch->file.xq) ||
			    !pch->had_frag) {
				pch->avail = 2;
				++nfree;
			}
			if (!pch->had_frag && i < ppp->nxchan)
				ppp->nxchan = i;
		}
		++i;
	}


	if (nfree == 0 || nfree < navail / 2)
		return 0;


	p = skb->data;
	len = skb->len;
	if (*p == 0) {
		++p;
		--len;
	}


	fragsize = len;
	if (nfree > 1)
		fragsize = DIV_ROUND_UP(fragsize, nfree);


	nbigger = len % nfree;


	list = &ppp->channels;
	for (i = 0; i < ppp->nxchan; ++i) {
		list = list->next;
		if (list == &ppp->channels) {
			i = 0;
			break;
		}
	}


	bits = B;
	while (nfree > 0 || len > 0) {
		list = list->next;
		if (list == &ppp->channels) {
			i = 0;
			continue;
		}
		pch = list_entry(list, struct channel, clist);
		++i;
		if (!pch->avail)
			continue;


		if (pch->avail == 1) {
			if (nfree > 0)
				continue;
		} else {
			--nfree;
			pch->avail = 1;
		}


		spin_lock_bh(&pch->downl);
		if (pch->chan == NULL) {

			spin_unlock_bh(&pch->downl);
			pch->avail = 0;
			if (--navail == 0)
				break;
			continue;
		}


		if (fragsize > len)
			fragsize = len;
		flen = fragsize;
		mtu = pch->chan->mtu + 2 - hdrlen;
		if (mtu < 4)
			mtu = 4;
		if (flen > mtu)
			flen = mtu;
		if (flen == len && nfree == 0)
			bits |= E;
		frag = alloc_skb(flen + hdrlen + (flen == 0), GFP_ATOMIC);
		if (!frag)
			goto noskb;
		q = skb_put(frag, flen + hdrlen);


		q[0] = PPP_MP >> 8;
		q[1] = PPP_MP;
		if (ppp->flags & SC_MP_XSHORTSEQ) {
			q[2] = bits + ((ppp->nxseq >> 8) & 0xf);
			q[3] = ppp->nxseq;
		} else {
			q[2] = bits;
			q[3] = ppp->nxseq >> 16;
			q[4] = ppp->nxseq >> 8;
			q[5] = ppp->nxseq;
		}


		if (flen == 0)
			*skb_put(frag, 1) = 0;
		else
			memcpy(q + hdrlen, p, flen);


		chan = pch->chan;
		if (!skb_queue_empty(&pch->file.xq) ||
		    !chan->ops->start_xmit(chan, frag))
			skb_queue_tail(&pch->file.xq, frag);
		pch->had_frag = 1;
		p += flen;
		len -= flen;
		++ppp->nxseq;
		bits = 0;
		spin_unlock_bh(&pch->downl);

		if (--nbigger == 0 && fragsize > 0)
			--fragsize;
	}
	ppp->nxchan = i;

	return 1;

 noskb:
	spin_unlock_bh(&pch->downl);
	if (ppp->debug & 1)
		printk(KERN_ERR "PPP: no memory (fragment)\n");
	++ppp->dev->stats.tx_errors;
	++ppp->nxseq;
	return 1;
}

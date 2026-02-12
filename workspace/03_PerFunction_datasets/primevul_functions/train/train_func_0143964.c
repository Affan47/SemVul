isdn_writebuf_skb_stub(int drvidx, int chan, int ack, struct sk_buff *skb)
{
	int ret;
	struct sk_buff *nskb = NULL;
	int v110_ret = skb->len;
	int idx = isdn_dc2minor(drvidx, chan);

	if (dev->v110[idx]) {
		atomic_inc(&dev->v110use[idx]);
		nskb = isdn_v110_encode(dev->v110[idx], skb);
		atomic_dec(&dev->v110use[idx]);
		if (!nskb)
			return 0;
		v110_ret = *((int *)nskb->data);
		skb_pull(nskb, sizeof(int));
		if (!nskb->len) {
			dev_kfree_skb(nskb);
			return v110_ret;
		}

		ack = 1;
		ret = dev->drv[drvidx]->interface->writebuf_skb(drvidx, chan, ack, nskb);
	} else {
		int hl = dev->drv[drvidx]->interface->hl_hdrlen;

		if (skb_headroom(skb) < hl) {


			struct sk_buff *skb_tmp;

			skb_tmp = skb_realloc_headroom(skb, hl);
			printk(KERN_DEBUG "isdn_writebuf_skb_stub: reallocating headroom%s\n", skb_tmp ? "" : " failed");
			if (!skb_tmp) return -ENOMEM;
			ret = dev->drv[drvidx]->interface->writebuf_skb(drvidx, chan, ack, skb_tmp);
			if (ret > 0) {
				dev_kfree_skb(skb);
			} else {
				dev_kfree_skb(skb_tmp);
			}
		} else {
			ret = dev->drv[drvidx]->interface->writebuf_skb(drvidx, chan, ack, skb);
		}
	}
	if (ret > 0) {
		dev->obytes[idx] += ret;
		if (dev->v110[idx]) {
			atomic_inc(&dev->v110use[idx]);
			dev->v110[idx]->skbuser++;
			atomic_dec(&dev->v110use[idx]);

			ret = v110_ret;


			if (ret == skb->len)
				dev_kfree_skb(skb);
		}
	} else
		if (dev->v110[idx])
			dev_kfree_skb(nskb);
	return ret;
}

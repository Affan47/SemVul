static void can_can_gw_rcv(struct sk_buff *skb, void *data)
{
	struct cgw_job *gwj = (struct cgw_job *)data;
	struct can_frame *cf;
	struct sk_buff *nskb;
	int modidx = 0;


#define cgw_hops(skb) ((skb)->csum_start)

	BUG_ON(skb->ip_summed != CHECKSUM_UNNECESSARY);

	if (cgw_hops(skb) >= max_hops) {

		gwj->deleted_frames++;
		return;
	}

	if (!(gwj->dst.dev->flags & IFF_UP)) {
		gwj->dropped_frames++;
		return;
	}


	if (!(gwj->flags & CGW_FLAGS_CAN_IIF_TX_OK) &&
	    can_skb_prv(skb)->ifindex == gwj->dst.dev->ifindex)
		return;


	if (gwj->mod.modfunc[0])
		nskb = skb_copy(skb, GFP_ATOMIC);
	else
		nskb = skb_clone(skb, GFP_ATOMIC);

	if (!nskb) {
		gwj->dropped_frames++;
		return;
	}


	cgw_hops(nskb) = cgw_hops(skb) + 1;


	if (gwj->limit_hops && cgw_hops(nskb) == 1)
		cgw_hops(nskb) = max_hops - gwj->limit_hops + 1;

	nskb->dev = gwj->dst.dev;


	cf = (struct can_frame *)nskb->data;


	while (modidx < MAX_MODFUNCTIONS && gwj->mod.modfunc[modidx])
		(*gwj->mod.modfunc[modidx++])(cf, &gwj->mod);


	if (modidx) {

		int max_len = nskb->len - offsetof(struct can_frame, data);


		if (cf->can_dlc > max_len)
			goto out_delete;


		if (gwj->mod.csumfunc.crc8) {
			if (cf->can_dlc > 8)
				goto out_delete;

			(*gwj->mod.csumfunc.crc8)(cf, &gwj->mod.csum.crc8);
		}

		if (gwj->mod.csumfunc.xor) {
			if (cf->can_dlc > 8)
				goto out_delete;

			(*gwj->mod.csumfunc.xor)(cf, &gwj->mod.csum.xor);
		}
	}


	if (!(gwj->flags & CGW_FLAGS_CAN_SRC_TSTAMP))
		nskb->tstamp = 0;


	if (can_send(nskb, gwj->flags & CGW_FLAGS_CAN_ECHO))
		gwj->dropped_frames++;
	else
		gwj->handled_frames++;

	return;

 out_delete:

	gwj->deleted_frames++;
	kfree_skb(nskb);
	return;
}

post_skb(struct uiscmdrsp *cmdrsp,
	 struct visornic_devdata *devdata, struct sk_buff *skb)
{
	cmdrsp->net.buf = skb;
	cmdrsp->net.rcvpost.frag.pi_pfn = page_to_pfn(virt_to_page(skb->data));
	cmdrsp->net.rcvpost.frag.pi_off =
		(unsigned long)skb->data & PI_PAGE_MASK;
	cmdrsp->net.rcvpost.frag.pi_len = skb->len;
	cmdrsp->net.rcvpost.unique_num = devdata->incarnation_id;

	if ((cmdrsp->net.rcvpost.frag.pi_off + skb->len) <= PI_PAGE_SIZE) {
		cmdrsp->net.type = NET_RCV_POST;
		cmdrsp->cmdtype = CMD_NET_TYPE;
		if (visorchannel_signalinsert(devdata->dev->visorchannel,
					  IOCHAN_TO_IOPART,
					  cmdrsp)) {
			atomic_inc(&devdata->num_rcvbuf_in_iovm);
			devdata->chstat.sent_post++;
		} else {
			devdata->chstat.sent_post_failed++;
		}
	}
}

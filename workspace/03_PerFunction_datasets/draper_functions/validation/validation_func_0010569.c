pass_open_rpl(struct c4iw_dev *dev, struct sk_buff *skb)
{
	struct cpl_pass_open_rpl *rpl = cplhdr(skb);
	struct tid_info *t = dev->rdev.lldi.tids;
	unsigned int stid = GET_TID(rpl);
	struct c4iw_listen_ep *ep = lookup_stid(t, stid);

	if (!ep) {
		PDBG("%s stid %d lookup failure!\n", __func__, stid);
		goto out;
	}
	PDBG("%s ep %p status %d error %d\n", __func__, ep,
	     rpl->status, status2errno(rpl->status));
	c4iw_wake_up(&ep->com.wr_wait, status2errno(rpl->status));

out:
	return 0;
}

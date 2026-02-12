isdn_ppp_release(int min, struct file *file)
{
	int i;
	struct ippp_struct *is;

	if (min < 0 || min >= ISDN_MAX_CHANNELS)
		return;
	is = file->private_data;

	if (!is) {
		printk(KERN_ERR "%s: no file->private_data\n", __func__);
		return;
	}
	if (is->debug & 0x1)
		printk(KERN_DEBUG "ippp: release, minor: %d %lx\n", min, (long) is->lp);

	if (is->lp) {
		isdn_net_dev *p = is->lp->netdev;

		if (!p) {
			printk(KERN_ERR "%s: no lp->netdev\n", __func__);
			return;
		}
		is->state &= ~IPPP_CONNECT;


		isdn_net_hangup(p->dev);
	}
	for (i = 0; i < NUM_RCV_BUFFS; i++) {
		kfree(is->rq[i].buf);
		is->rq[i].buf = NULL;
	}
	is->first = is->rq + NUM_RCV_BUFFS - 1;
	is->last = is->rq;

#ifdef CONFIG_ISDN_PPP_VJ

	slhc_free(is->slcomp);
	is->slcomp = NULL;
#endif
#ifdef CONFIG_IPPP_FILTER
	if (is->pass_filter) {
		bpf_prog_destroy(is->pass_filter);
		is->pass_filter = NULL;
	}

	if (is->active_filter) {
		bpf_prog_destroy(is->active_filter);
		is->active_filter = NULL;
	}
#endif


	if (is->comp_stat)
		is->compressor->free(is->comp_stat);
	if (is->link_comp_stat)
		is->link_compressor->free(is->link_comp_stat);
	if (is->link_decomp_stat)
		is->link_decompressor->free(is->link_decomp_stat);
	if (is->decomp_stat)
		is->decompressor->free(is->decomp_stat);
	is->compressor   = is->link_compressor   = NULL;
	is->decompressor = is->link_decompressor = NULL;
	is->comp_stat    = is->link_comp_stat    = NULL;
	is->decomp_stat  = is->link_decomp_stat  = NULL;


	if (is->reset)
		isdn_ppp_ccp_reset_free(is);


	is->state = 0;
}

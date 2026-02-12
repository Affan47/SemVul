static void isdn_ppp_ccp_reset_trans(struct ippp_struct *is,
				     struct isdn_ppp_resetparams *rp)
{
	struct ippp_ccp_reset_state *rs;

	if (rp->valid) {

		if (rp->rsend) {

			if (!(rp->idval)) {
				printk(KERN_ERR "ippp_ccp: decompressor must"
				       " specify reset id\n");
				return;
			}
			if (is->reset->rs[rp->id]) {


				rs = is->reset->rs[rp->id];
				if (rs->state == CCPResetSentReq && rs->ta) {
					printk(KERN_DEBUG "ippp_ccp: reset"
					       " trans still in progress"
					       " for id %d\n", rp->id);
				} else {
					printk(KERN_WARNING "ippp_ccp: reset"
					       " trans in wrong state %d for"
					       " id %d\n", rs->state, rp->id);
				}
			} else {

				printk(KERN_DEBUG "ippp_ccp: new trans for id"
				       " %d to be started\n", rp->id);
				rs = isdn_ppp_ccp_reset_alloc_state(is, rp->id);
				if (!rs) {
					printk(KERN_ERR "ippp_ccp: out of mem"
					       " allocing ccp trans\n");
					return;
				}
				rs->state = CCPResetSentReq;
				rs->expra = rp->expra;
				if (rp->dtval) {
					rs->dlen = rp->dlen;
					memcpy(rs->data, rp->data, rp->dlen);
				}

				isdn_ppp_ccp_xmit_reset(is, PPP_CCP,
							CCP_RESETREQ, rs->id,
							rs->data, rs->dlen);

				rs->timer.expires = jiffies + 5 * HZ;
				add_timer(&rs->timer);
				rs->ta = 1;
			}
		} else {
			printk(KERN_DEBUG "ippp_ccp: no reset sent\n");
		}
	} else {


		if (is->reset->rs[is->reset->lastid]) {


			rs = is->reset->rs[is->reset->lastid];
			if (rs->state == CCPResetSentReq && rs->ta) {
				printk(KERN_DEBUG "ippp_ccp: reset"
				       " trans still in progress"
				       " for id %d\n", rp->id);
			} else {
				printk(KERN_WARNING "ippp_ccp: reset"
				       " trans in wrong state %d for"
				       " id %d\n", rs->state, rp->id);
			}
		} else {
			printk(KERN_DEBUG "ippp_ccp: new trans for id"
			       " %d to be started\n", is->reset->lastid);
			rs = isdn_ppp_ccp_reset_alloc_state(is,
							    is->reset->lastid);
			if (!rs) {
				printk(KERN_ERR "ippp_ccp: out of mem"
				       " allocing ccp trans\n");
				return;
			}
			rs->state = CCPResetSentReq;


			rs->expra = 1;
			rs->dlen = 0;

			isdn_ppp_ccp_xmit_reset(is, PPP_CCP, CCP_RESETREQ,
						rs->id, NULL, 0);

			rs->timer.expires = jiffies + 5 * HZ;
			add_timer(&rs->timer);
			rs->ta = 1;
		}
	}
}

nfsd4_return_file_layouts(struct svc_rqst *rqstp,
		struct nfsd4_compound_state *cstate,
		struct nfsd4_layoutreturn *lrp)
{
	struct nfs4_layout_stateid *ls;
	struct nfs4_layout *lp, *n;
	LIST_HEAD(reaplist);
	__be32 nfserr;
	int found = 0;

	nfserr = nfsd4_preprocess_layout_stateid(rqstp, cstate, &lrp->lr_sid,
						false, lrp->lr_layout_type,
						&ls);
	if (nfserr) {
		trace_layout_return_lookup_fail(&lrp->lr_sid);
		return nfserr;
	}

	spin_lock(&ls->ls_lock);
	list_for_each_entry_safe(lp, n, &ls->ls_layouts, lo_perstate) {
		if (layouts_overlapping(lp, &lrp->lr_seg)) {
			nfsd4_return_file_layout(lp, &lrp->lr_seg, &reaplist);
			found++;
		}
	}
	if (!list_empty(&ls->ls_layouts)) {
		if (found)
			nfs4_inc_and_copy_stateid(&lrp->lr_sid, &ls->ls_stid);
		lrp->lrs_present = 1;
	} else {
		trace_layoutstate_unhash(&ls->ls_stid.sc_stateid);
		nfs4_unhash_stid(&ls->ls_stid);
		lrp->lrs_present = 0;
	}
	spin_unlock(&ls->ls_lock);

	mutex_unlock(&ls->ls_mutex);
	nfs4_put_stid(&ls->ls_stid);
	nfsd4_free_layouts(&reaplist);
	return nfs_ok;
}

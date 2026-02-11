cxgb4_free_stid(struct tid_info *t, unsigned int stid, int family)
{

	if (t->nsftids && (stid >= t->sftid_base)) {
		stid -= t->sftid_base;
		stid += t->nstids;
	} else {
		stid -= t->stid_base;
	}

	spin_lock_bh(&t->stid_lock);
	if (family == PF_INET)
		__clear_bit(stid, t->stid_bmap);
	else
		bitmap_release_region(t->stid_bmap, stid, 2);
	t->stid_tab[stid].data = NULL;
	if (stid < t->nstids) {
		if (family == PF_INET)
			t->stids_in_use--;
		else
			t->stids_in_use -= 4;
	} else {
		t->sftids_in_use--;
	}
	spin_unlock_bh(&t->stid_lock);
}

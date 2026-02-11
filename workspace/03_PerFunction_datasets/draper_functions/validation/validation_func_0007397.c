__dquot_free_space(struct inode *inode, qsize_t number, int flags)
{
	unsigned int cnt;
	struct dquot_warn warn[MAXQUOTAS];
	struct dquot **dquots;
	int reserve = flags & DQUOT_SPACE_RESERVE, index;

	if (!dquot_active(inode)) {
		inode_decr_space(inode, number, reserve);
		return;
	}

	dquots = i_dquot(inode);
	index = srcu_read_lock(&dquot_srcu);
	spin_lock(&dq_data_lock);
	for (cnt = 0; cnt < MAXQUOTAS; cnt++) {
		int wtype;

		warn[cnt].w_type = QUOTA_NL_NOWARN;
		if (!dquots[cnt])
			continue;
		wtype = info_bdq_free(dquots[cnt], number);
		if (wtype != QUOTA_NL_NOWARN)
			prepare_warning(&warn[cnt], dquots[cnt], wtype);
		if (reserve)
			dquot_free_reserved_space(dquots[cnt], number);
		else
			dquot_decr_space(dquots[cnt], number);
	}
	inode_decr_space(inode, number, reserve);
	spin_unlock(&dq_data_lock);

	if (reserve)
		goto out_unlock;
	mark_all_dquot_dirty(dquots);
out_unlock:
	srcu_read_unlock(&dquot_srcu, index);
	flush_warnings(warn);
}

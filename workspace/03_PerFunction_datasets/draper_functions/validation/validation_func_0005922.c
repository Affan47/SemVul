restart_transaction(struct reiserfs_transaction_handle *th,
			       struct inode *inode, struct treepath *path)
{
	struct super_block *s = th->t_super;
	int err;

	BUG_ON(!th->t_trans_id);
	BUG_ON(!th->t_refcount);

	pathrelse(path);


	if (th->t_refcount > 1) {
		return 0;
	}
	reiserfs_update_sd(th, inode);
	err = journal_end(th);
	if (!err) {
		err = journal_begin(th, s, JOURNAL_PER_BALANCE_CNT * 6);
		if (!err)
			reiserfs_update_inode_transaction(inode);
	}
	return err;
}

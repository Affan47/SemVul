may_rename_srcdir(struct dentry *dentry, aufs_bindex_t btgt)
{
	int err;
	unsigned int rdhash;
	aufs_bindex_t bstart;

	bstart = au_dbstart(dentry);
	if (bstart != btgt) {
		struct au_nhash whlist;

		SiMustAnyLock(dentry->d_sb);
		rdhash = au_sbi(dentry->d_sb)->si_rdhash;
		if (!rdhash)
			rdhash = au_rdhash_est(au_dir_size(NULL,
							   dentry));
		err = au_nhash_alloc(&whlist, rdhash, GFP_NOFS);
		if (unlikely(err))
			goto out;
		err = au_test_empty(dentry, &whlist);
		au_nhash_wh_free(&whlist);
		goto out;
	}

	if (bstart == au_dbtaildir(dentry))
		return 0;

	err = au_test_empty_lower(dentry);

out:
	if (err == -ENOTEMPTY) {
		AuWarn1("renaming dir who has child(ren) on multiple branches,"
			" is not supported\n");
		err = -EXDEV;
	}
	return err;
}

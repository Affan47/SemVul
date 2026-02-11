au_wbr_init(struct au_branch *br, struct super_block *sb,
		       int perm)
{
	int err;
	struct kstatfs kst;
	struct au_wbr *wbr;

	wbr = br->br_wbr;
	au_rw_init(&wbr->wbr_wh_rwsem);
	atomic_set(&wbr->wbr_wh_running, 0);


	err = vfs_statfs(&br->br_path, &kst);
	if (unlikely(err))
		goto out;
	err = -EINVAL;
	if (kst.f_namelen >= NAME_MAX)
		err = au_br_init_wh(sb, br, perm);
	else
		pr_err("%pd(%s), unsupported namelen %ld\n",
		       au_br_dentry(br),
		       au_sbtype(au_br_dentry(br)->d_sb), kst.f_namelen);

out:
	return err;
}

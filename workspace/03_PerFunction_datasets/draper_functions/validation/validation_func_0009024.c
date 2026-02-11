sysaufs_si_br(struct seq_file *seq, struct super_block *sb,
			 aufs_bindex_t bindex, int idx)
{
	int err;
	struct path path;
	struct dentry *root;
	struct au_branch *br;
	au_br_perm_str_t perm;

	AuDbg("b%d\n", bindex);

	err = 0;
	root = sb->s_root;
	di_read_lock_parent(root, !AuLock_IR);
	br = au_sbr(sb, bindex);

	switch (idx) {
	case AuBrSysfs_BR:
		path.mnt = au_br_mnt(br);
		path.dentry = au_h_dptr(root, bindex);
		err = au_seq_path(seq, &path);
		if (!err) {
			au_optstr_br_perm(&perm, br->br_perm);
			seq_printf(seq, "=%s\n", perm.a);
		}
		break;
	case AuBrSysfs_BRID:
		seq_printf(seq, "%d\n", br->br_id);
		break;
	}
	di_read_unlock(root, !AuLock_IR);
	if (unlikely(err || seq_has_overflowed(seq)))
		err = -E2BIG;

	return err;
}

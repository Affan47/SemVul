static int lookup_umount_fs_by_statfs(struct libmnt_context *cxt, const char *tgt)
{
	struct stat st;
	const char *type;

	assert(cxt);
	assert(cxt->fs);

	DBG(CXT, ul_debugobj(cxt, " lookup by statfs"));


	if (mnt_context_is_restricted(cxt)
	    || *tgt != '/'
	    || (cxt->flags & MNT_FL_HELPER)
	    || mnt_context_mtab_writable(cxt)
	    || mnt_context_is_force(cxt)
	    || mnt_context_is_lazy(cxt)
	    || mnt_context_is_nocanonicalize(cxt)
	    || mnt_context_is_loopdel(cxt)
	    || mnt_stat_mountpoint(tgt, &st) != 0 || !S_ISDIR(st.st_mode)
	    || has_utab_entry(cxt, tgt))
		return 1;

	type = mnt_fs_get_fstype(cxt->fs);
	if (!type) {
		struct statfs vfs;
		int fd;

		DBG(CXT, ul_debugobj(cxt, "  trying fstatfs()"));


		fd = open(tgt, O_PATH);
		if (fd >= 0) {
			if (fstatfs(fd, &vfs) == 0)
				type = mnt_statfs_get_fstype(&vfs);
			close(fd);
		}
		if (type) {
			int rc = mnt_fs_set_fstype(cxt->fs, type);
			if (rc)
				return rc;
		}
	}
	if (type) {
		DBG(CXT, ul_debugobj(cxt, "  umount: disabling mtab"));
		mnt_context_disable_mtab(cxt, TRUE);

		DBG(CXT, ul_debugobj(cxt,
			"  mountinfo unnecessary [type=%s]", type));
		return 0;
	}

	return 1;
}

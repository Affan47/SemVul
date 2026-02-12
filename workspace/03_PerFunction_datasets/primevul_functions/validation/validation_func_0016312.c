int mnt_context_find_umount_fs(struct libmnt_context *cxt,
			       const char *tgt,
			       struct libmnt_fs **pfs)
{
	if (pfs)
		*pfs = NULL;

	if (!cxt || !tgt || !pfs)
		return -EINVAL;

	DBG(CXT, ul_debugobj(cxt, "umount: lookup FS for '%s'", tgt));

	if (!*tgt)
		return 1;


	return __mtab_find_umount_fs(cxt, tgt, pfs);
}

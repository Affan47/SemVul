static int nfs4_opendata_access(const struct cred *cred,
				struct nfs4_opendata *opendata,
				struct nfs4_state *state, fmode_t fmode,
				int openflags)
{
	struct nfs_access_entry cache;
	u32 mask, flags;


	if (opendata->o_res.access_supported == 0)
		return 0;

	mask = 0;


	if (openflags & __FMODE_EXEC) {

		if (S_ISDIR(state->inode->i_mode))
			mask = NFS4_ACCESS_LOOKUP;
		else
			mask = NFS4_ACCESS_EXECUTE;
	} else if ((fmode & FMODE_READ) && !opendata->file_created)
		mask = NFS4_ACCESS_READ;

	cache.cred = cred;
	nfs_access_set_mask(&cache, opendata->o_res.access_result);
	nfs_access_add_cache(state->inode, &cache);

	flags = NFS4_ACCESS_READ | NFS4_ACCESS_EXECUTE | NFS4_ACCESS_LOOKUP;
	if ((mask & ~cache.mask & flags) == 0)
		return 0;

	return -EACCES;
}

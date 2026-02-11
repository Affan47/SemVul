nfs_lookup(struct inode *dir, struct dentry * dentry, unsigned int flags)
{
	struct dentry *res;
	struct dentry *parent;
	struct inode *inode = NULL;
	struct nfs_fh *fhandle = NULL;
	struct nfs_fattr *fattr = NULL;
	struct nfs4_label *label = NULL;
	int error;

	dfprintk(VFS, "NFS: lookup(%pd2)\n", dentry);
	nfs_inc_stats(dir, NFSIOS_VFSLOOKUP);

	res = ERR_PTR(-ENAMETOOLONG);
	if (dentry->d_name.len > NFS_SERVER(dir)->namelen)
		goto out;


	if (nfs_is_exclusive_create(dir, flags)) {
		d_instantiate(dentry, NULL);
		res = NULL;
		goto out;
	}

	res = ERR_PTR(-ENOMEM);
	fhandle = nfs_alloc_fhandle();
	fattr = nfs_alloc_fattr();
	if (fhandle == NULL || fattr == NULL)
		goto out;

	label = nfs4_label_alloc(NFS_SERVER(dir), GFP_NOWAIT);
	if (IS_ERR(label))
		goto out;

	parent = dentry->d_parent;

	trace_nfs_lookup_enter(dir, dentry, flags);
	nfs_block_sillyrename(parent);
	error = NFS_PROTO(dir)->lookup(dir, &dentry->d_name, fhandle, fattr, label);
	if (error == -ENOENT)
		goto no_entry;
	if (error < 0) {
		res = ERR_PTR(error);
		goto out_unblock_sillyrename;
	}
	inode = nfs_fhget(dentry->d_sb, fhandle, fattr, label);
	res = ERR_CAST(inode);
	if (IS_ERR(res))
		goto out_unblock_sillyrename;


	nfs_advise_use_readdirplus(dir);

no_entry:
	res = d_splice_alias(inode, dentry);
	if (res != NULL) {
		if (IS_ERR(res))
			goto out_unblock_sillyrename;
		dentry = res;
	}
	nfs_set_verifier(dentry, nfs_save_change_attribute(dir));
out_unblock_sillyrename:
	nfs_unblock_sillyrename(parent);
	trace_nfs_lookup_exit(dir, dentry, flags, error);
	nfs4_label_free(label);
out:
	nfs_free_fattr(fattr);
	nfs_free_fhandle(fhandle);
	return res;
}

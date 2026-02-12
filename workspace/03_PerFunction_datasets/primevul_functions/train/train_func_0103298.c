int nfs_instantiate(struct dentry *dentry, struct nfs_fh *fhandle,
				struct nfs_fattr *fattr)
{
	struct dentry *d;

	d = nfs_add_or_obtain(dentry, fhandle, fattr);
	if (IS_ERR(d))
		return PTR_ERR(d);


	dput(d);
	return 0;
}

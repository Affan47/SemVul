struct file *nameidata_to_filp(struct nameidata *nd, int flags)
{
	struct file *filp;


	filp = nd->intent.open.file;

	if (filp->f_path.dentry == NULL)
		filp = __dentry_open(nd->dentry, nd->mnt, flags, filp, NULL);
	else
		path_release(nd);
	return filp;
}

hfsplus_getxattr(struct dentry *dentry, const char *name,
			 void *value, size_t size,
			 const char *prefix, size_t prefixlen)
{
	int res;
	char *xattr_name;

	if (!strcmp(name, ""))
		return -EINVAL;

	xattr_name = kmalloc(NLS_MAX_CHARSET_SIZE * HFSPLUS_ATTR_MAX_STRLEN + 1,
			     GFP_KERNEL);
	if (!xattr_name)
		return -ENOMEM;

	strcpy(xattr_name, prefix);
	strcpy(xattr_name + prefixlen, name);

	res = __hfsplus_getxattr(d_inode(dentry), xattr_name, value, size);
	kfree(xattr_name);
	return res;

}

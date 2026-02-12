static int smack_inode_copy_up_xattr(const char *name)
{


	if (strcmp(name, XATTR_NAME_SMACK) == 0)
		return 1;

	return -EOPNOTSUPP;
}

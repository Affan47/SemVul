xfs_attr_match(
	struct xfs_da_args	*args,
	uint8_t			namelen,
	unsigned char		*name,
	int			flags)
{
	if (args->namelen != namelen)
		return false;
	if (memcmp(args->name, name, namelen) != 0)
		return false;


	if (args->attr_filter !=
	    (flags & (XFS_ATTR_NSP_ONDISK_MASK | XFS_ATTR_INCOMPLETE)))
		return false;
	return true;
}

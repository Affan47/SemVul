xfs_dir3_data_put_ftype(
	struct xfs_dir2_data_entry *dep,
	__uint8_t		type)
{
	ASSERT(type < XFS_DIR3_FT_MAX);
	ASSERT(dep->namelen != 0);

	dep->name[dep->namelen] = type;
}

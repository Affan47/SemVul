const char *btrfs_super_csum_driver(u16 csum_type)
{

	return btrfs_csums[csum_type].driver[0] ?
		btrfs_csums[csum_type].driver :
		btrfs_csums[csum_type].name;
}

static loff_t ext4_max_size(int blkbits, int has_huge_files)
{
	loff_t res;
	loff_t upper_limit = MAX_LFS_FILESIZE;

	BUILD_BUG_ON(sizeof(blkcnt_t) < sizeof(u64));

	if (!has_huge_files) {
		upper_limit = (1LL << 32) - 1;


		upper_limit >>= (blkbits - 9);
		upper_limit <<= blkbits;
	}


	res = (1LL << 32) - 1;
	res <<= blkbits;


	if (res > upper_limit)
		res = upper_limit;

	return res;
}

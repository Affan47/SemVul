nilfs_valid_sb(struct nilfs_super_block *sbp)
{
	static unsigned char sum[4];
	const int sumoff = offsetof(struct nilfs_super_block, s_sum);
	size_t bytes;
	u32 crc;

	if (!sbp || le16_to_cpu(sbp->s_magic) != NILFS_SUPER_MAGIC)
		return 0;
	bytes = le16_to_cpu(sbp->s_bytes);
	if (bytes < sumoff + 4 || bytes > BLOCK_SIZE)
		return 0;
	crc = crc32_le(le32_to_cpu(sbp->s_crc_seed), (unsigned char *)sbp,
		       sumoff);
	crc = crc32_le(crc, sum, 4);
	crc = crc32_le(crc, (unsigned char *)sbp + sumoff + 4,
		       bytes - sumoff - 4);
	return crc == le32_to_cpu(sbp->s_sum);
}

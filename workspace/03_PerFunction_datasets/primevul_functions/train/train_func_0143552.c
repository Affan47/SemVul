int __ext4_xattr_set_credits(struct super_block *sb, struct inode *inode,
			     struct buffer_head *block_bh, size_t value_len,
			     bool is_create)
{
	int credits;
	int blocks;


	credits = 7;


	credits += EXT4_MAXQUOTAS_TRANS_BLOCKS(sb);


	if (inode && ext4_has_inline_data(inode))
		credits += ext4_writepage_trans_blocks(inode) + 1;


	if (!ext4_has_feature_ea_inode(sb))
		return credits;


	credits += 4;


	blocks = (value_len + sb->s_blocksize - 1) >> sb->s_blocksize_bits;


	blocks += 1;


	credits += blocks * 2;


	credits += blocks;

	if (!is_create) {


		credits += 4;


		blocks = XATTR_SIZE_MAX >> sb->s_blocksize_bits;


		blocks += 1;


		credits += blocks * 2;
	}


	if (block_bh) {
		struct ext4_xattr_entry *entry = BFIRST(block_bh);

		for (; !IS_LAST_ENTRY(entry); entry = EXT4_XATTR_NEXT(entry))
			if (entry->e_value_inum)

				credits += 1;
	}
	return credits;
}

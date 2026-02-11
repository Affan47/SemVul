fsck_chk_dentry_blk(struct f2fs_sb_info *sbi,
		struct f2fs_inode *inode,
		u32 blk_addr,
		u32 *child_cnt,
		u32 *child_files,
		int last_blk)
{
	struct f2fs_fsck *fsck = F2FS_FSCK(sbi);
	int i;
	int ret = 0;
	int dentries = 0;
	u8 *name;
	u32 hash_code;
	u32 blk_cnt;
	u16 name_len;;

	enum FILE_TYPE ftype;
	struct f2fs_dentry_block *de_blk;

	de_blk = (struct f2fs_dentry_block *)calloc(BLOCK_SZ, 1);
	ASSERT(de_blk != NULL);

	ret = dev_read_block(de_blk, blk_addr);
	ASSERT(ret >= 0);

	fsck->dentry_depth++;

	for (i = 0; i < NR_DENTRY_IN_BLOCK;) {
		if (test_bit(i, (unsigned long *)de_blk->dentry_bitmap) == 0x0) {
			i++;
			continue;
		}

		name_len = le32_to_cpu(de_blk->dentry[i].name_len);
		name = calloc(name_len + 1, 1);
		memcpy(name, de_blk->filename[i], name_len);

		hash_code = f2fs_dentry_hash((const char *)name, name_len);
		ASSERT(le32_to_cpu(de_blk->dentry[i].hash_code) == hash_code);

		ftype = de_blk->dentry[i].file_type;


		if (ftype == F2FS_FT_DIR) {
			*child_cnt = *child_cnt + 1;
			if ((name[0] == '.' && name[1] == '.' && name_len == 2) ||
					(name[0] == '.' && name_len == 1)) {
				i++;
				free(name);
				continue;
			}
		}

		DBG(2, "[%3u] - no[0x%x] name[%s] len[0x%x] ino[0x%x] type[0x%x]\n",
				fsck->dentry_depth, i, name, name_len,
				le32_to_cpu(de_blk->dentry[i].ino),
				de_blk->dentry[i].file_type);

		print_dentry(fsck->dentry_depth, name, de_blk, i, last_blk);

		blk_cnt = 1;
		ret = fsck_chk_node_blk(sbi,
				NULL,
				le32_to_cpu(de_blk->dentry[i].ino),
				ftype,
				TYPE_INODE,
				&blk_cnt);

		ASSERT(ret >= 0);

		i += (name_len + F2FS_SLOT_LEN - 1) / F2FS_SLOT_LEN;
		dentries++;
		*child_files = *child_files + 1;
		free(name);
	}

	DBG(1, "[%3d] Dentry Block [0x%x] Done : dentries:%d in %d slots (len:%d)\n\n",
			fsck->dentry_depth, blk_addr, dentries, NR_DENTRY_IN_BLOCK, F2FS_NAME_LEN);
	fsck->dentry_depth--;

	free(de_blk);
	return 0;
}

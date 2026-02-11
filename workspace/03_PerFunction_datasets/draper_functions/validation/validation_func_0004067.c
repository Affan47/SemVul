get_valid_checkpoint(struct f2fs_sb_info *sbi)
{
	struct f2fs_super_block *raw_sb = sbi->raw_super;
	void *cp1, *cp2, *cur_page;
	unsigned long blk_size = sbi->blocksize;
	unsigned long long cp1_version = 0, cp2_version = 0;
	unsigned long long cp_start_blk_no;

	sbi->ckpt = malloc(blk_size);
	if (!sbi->ckpt)
		return -ENOMEM;


	cp_start_blk_no = le32_to_cpu(raw_sb->cp_blkaddr);
	cp1 = validate_checkpoint(sbi, cp_start_blk_no, &cp1_version);


	cp_start_blk_no += 1 << le32_to_cpu(raw_sb->log_blocks_per_seg);
	cp2 = validate_checkpoint(sbi, cp_start_blk_no, &cp2_version);

	if (cp1 && cp2) {
		if (ver_after(cp2_version, cp1_version))
			cur_page = cp2;
		else
			cur_page = cp1;
	} else if (cp1) {
		cur_page = cp1;
	} else if (cp2) {
		cur_page = cp2;
	} else {
		free(cp1);
		free(cp2);
		goto fail_no_cp;
	}

	memcpy(sbi->ckpt, cur_page, blk_size);

	free(cp1);
	free(cp2);
	return 0;

fail_no_cp:
	free(sbi->ckpt);
	return -EINVAL;
}

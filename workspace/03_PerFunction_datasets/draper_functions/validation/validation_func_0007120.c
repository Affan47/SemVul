udf_bitmap_free_blocks(struct super_block *sb,
				   struct udf_bitmap *bitmap,
				   struct kernel_lb_addr *bloc,
				   uint32_t offset,
				   uint32_t count)
{
	struct udf_sb_info *sbi = UDF_SB(sb);
	struct buffer_head *bh = NULL;
	struct udf_part_map *partmap;
	unsigned long block;
	unsigned long block_group;
	unsigned long bit;
	unsigned long i;
	int bitmap_nr;
	unsigned long overflow;

	mutex_lock(&sbi->s_alloc_mutex);
	partmap = &sbi->s_partmaps[bloc->partitionReferenceNum];
	if (bloc->logicalBlockNum + count < count ||
	    (bloc->logicalBlockNum + count) > partmap->s_partition_len) {
		udf_debug("%d < %d || %d + %d > %d\n",
			  bloc->logicalBlockNum, 0,
			  bloc->logicalBlockNum, count,
			  partmap->s_partition_len);
		goto error_return;
	}

	block = bloc->logicalBlockNum + offset +
		(sizeof(struct spaceBitmapDesc) << 3);

	do {
		overflow = 0;
		block_group = block >> (sb->s_blocksize_bits + 3);
		bit = block % (sb->s_blocksize << 3);


		if (bit + count > (sb->s_blocksize << 3)) {
			overflow = bit + count - (sb->s_blocksize << 3);
			count -= overflow;
		}
		bitmap_nr = load_block_bitmap(sb, bitmap, block_group);
		if (bitmap_nr < 0)
			goto error_return;

		bh = bitmap->s_block_bitmap[bitmap_nr];
		for (i = 0; i < count; i++) {
			if (udf_set_bit(bit + i, bh->b_data)) {
				udf_debug("bit %ld already set\n", bit + i);
				udf_debug("byte=%2x\n",
					  ((char *)bh->b_data)[(bit + i) >> 3]);
			}
		}
		udf_add_free_space(sb, sbi->s_partition, count);
		mark_buffer_dirty(bh);
		if (overflow) {
			block += count;
			count = overflow;
		}
	} while (overflow);

error_return:
	mutex_unlock(&sbi->s_alloc_mutex);
}

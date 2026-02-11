build_block_map(struct partition *part, int block_no)
{
	struct block *block = &part->blocks[block_no];
	int i;

	block->offset = part->block_size * block_no;

	if (le16_to_cpu(part->header_cache[0]) != RFD_MAGIC) {
		block->state = BLOCK_UNUSED;
		return -ENOENT;
	}

	block->state = BLOCK_OK;

	for (i=0; i<part->data_sectors_per_block; i++) {
		u16 entry;

		entry = le16_to_cpu(part->header_cache[HEADER_MAP_OFFSET + i]);

		if (entry == SECTOR_DELETED)
			continue;

		if (entry == SECTOR_FREE) {
			block->free_sectors++;
			continue;
		}

		if (entry == SECTOR_ZERO)
			entry = 0;

		if (entry >= part->sector_count) {
			printk(KERN_WARNING PREFIX
				"'%s': unit #%d: entry %d corrupt, "
				"sector %d out of range\n",
				part->mbd.mtd->name, block_no, i, entry);
			continue;
		}

		if (part->sector_map[entry] != -1) {
			printk(KERN_WARNING PREFIX
				"'%s': more than one entry for sector %d\n",
				part->mbd.mtd->name, entry);
			part->errors = 1;
			continue;
		}

		part->sector_map[entry] = block->offset +
			(i + part->header_sectors_per_block) * SECTOR_SIZE;

		block->used_sectors++;
	}

	if (block->free_sectors == part->data_sectors_per_block)
		part->reserved_block = block_no;

	return 0;
}

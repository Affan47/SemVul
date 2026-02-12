static struct btrfs_super_block *btrfs_read_disk_super(struct block_device *bdev,
						       u64 bytenr, u64 bytenr_orig)
{
	struct btrfs_super_block *disk_super;
	struct page *page;
	void *p;
	pgoff_t index;


	if (bytenr + PAGE_SIZE >= i_size_read(bdev->bd_inode))
		return ERR_PTR(-EINVAL);


	if (sizeof(*disk_super) > PAGE_SIZE)
		return ERR_PTR(-EINVAL);


	index = bytenr >> PAGE_SHIFT;
	if ((bytenr + sizeof(*disk_super) - 1) >> PAGE_SHIFT != index)
		return ERR_PTR(-EINVAL);


	page = read_cache_page_gfp(bdev->bd_inode->i_mapping, index, GFP_KERNEL);

	if (IS_ERR(page))
		return ERR_CAST(page);

	p = page_address(page);


	disk_super = p + offset_in_page(bytenr);

	if (btrfs_super_bytenr(disk_super) != bytenr_orig ||
	    btrfs_super_magic(disk_super) != BTRFS_MAGIC) {
		btrfs_release_disk_super(p);
		return ERR_PTR(-EINVAL);
	}

	if (disk_super->label[0] && disk_super->label[BTRFS_LABEL_SIZE - 1])
		disk_super->label[BTRFS_LABEL_SIZE - 1] = 0;

	return disk_super;
}

static int shmem_writepage(struct page *page, struct writeback_control *wbc)
{
	struct shmem_inode_info *info;
	swp_entry_t *entry, swap;
	struct address_space *mapping;
	unsigned long index;
	struct inode *inode;

	BUG_ON(!PageLocked(page));


	if (!wbc->for_reclaim) {
		set_page_dirty(page);
		unlock_page(page);
		return 0;
	}
	BUG_ON(page_mapped(page));

	mapping = page->mapping;
	index = page->index;
	inode = mapping->host;
	info = SHMEM_I(inode);
	if (info->flags & VM_LOCKED)
		goto redirty;
	swap = get_swap_page();
	if (!swap.val)
		goto redirty;

	spin_lock(&info->lock);
	shmem_recalc_inode(inode);
	if (index >= info->next_index) {
		BUG_ON(!(info->flags & SHMEM_TRUNCATE));
		goto unlock;
	}
	entry = shmem_swp_entry(info, index, NULL);
	BUG_ON(!entry);
	BUG_ON(entry->val);

	if (move_to_swap_cache(page, swap) == 0) {
		shmem_swp_set(info, entry, swap.val);
		shmem_swp_unmap(entry);
		spin_unlock(&info->lock);
		if (list_empty(&info->swaplist)) {
			spin_lock(&shmem_swaplist_lock);

			list_move_tail(&info->swaplist, &shmem_swaplist);
			spin_unlock(&shmem_swaplist_lock);
		}
		unlock_page(page);
		return 0;
	}

	shmem_swp_unmap(entry);
unlock:
	spin_unlock(&info->lock);
	swap_free(swap);
redirty:
	set_page_dirty(page);
	return AOP_WRITEPAGE_ACTIVATE;
}

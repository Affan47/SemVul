gennvm_get_blk_unlocked(struct nvm_dev *dev,
				struct nvm_lun *vlun, unsigned long flags)
{
	struct gen_lun *lun = container_of(vlun, struct gen_lun, vlun);
	struct nvm_block *blk = NULL;
	int is_gc = flags & NVM_IOTYPE_GC;

	assert_spin_locked(&vlun->lock);

	if (list_empty(&lun->free_list)) {
		pr_err_ratelimited("gennvm: lun %u have no free pages available",
								lun->vlun.id);
		goto out;
	}

	if (!is_gc && lun->vlun.nr_free_blocks < lun->reserved_blocks)
		goto out;

	blk = list_first_entry(&lun->free_list, struct nvm_block, list);
	list_move_tail(&blk->list, &lun->used_list);
	blk->state = NVM_BLK_ST_OPEN;

	lun->vlun.nr_free_blocks--;
	lun->vlun.nr_open_blocks++;

out:
	return blk;
}

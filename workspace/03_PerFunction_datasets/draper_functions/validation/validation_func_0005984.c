requeue_inode(struct inode *inode, struct bdi_writeback *wb,
			  struct writeback_control *wbc)
{
	if (inode->i_state & I_FREEING)
		return;


	if ((inode->i_state & I_DIRTY) &&
	    (wbc->sync_mode == WB_SYNC_ALL || wbc->tagged_writepages))
		inode->dirtied_when = jiffies;

	if (wbc->pages_skipped) {


		redirty_tail(inode, wb);
		return;
	}

	if (mapping_tagged(inode->i_mapping, PAGECACHE_TAG_DIRTY)) {


		if (wbc->nr_to_write <= 0) {

			requeue_io(inode, wb);
		} else {


			redirty_tail(inode, wb);
		}
	} else if (inode->i_state & I_DIRTY) {


		redirty_tail(inode, wb);
	} else if (inode->i_state & I_DIRTY_TIME) {
		inode->dirtied_when = jiffies;
		inode_io_list_move_locked(inode, wb, &wb->b_dirty_time);
	} else {

		inode_io_list_del_locked(inode, wb);
	}
}

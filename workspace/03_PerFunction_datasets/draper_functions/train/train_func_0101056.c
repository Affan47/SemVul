btrfs_init_compress(void)
{
	int i;

	for (i = 0; i < BTRFS_COMPRESS_TYPES; i++) {
		INIT_LIST_HEAD(&btrfs_comp_ws[i].idle_ws);
		spin_lock_init(&btrfs_comp_ws[i].ws_lock);
		atomic_set(&btrfs_comp_ws[i].alloc_ws, 0);
		init_waitqueue_head(&btrfs_comp_ws[i].ws_wait);
	}
}

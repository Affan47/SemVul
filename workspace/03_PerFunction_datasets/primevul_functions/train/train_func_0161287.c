xfs_init_workqueues(void)
{


	xfs_alloc_wq = alloc_workqueue("xfsalloc",
			WQ_MEM_RECLAIM|WQ_FREEZABLE, 0);
	if (!xfs_alloc_wq)
		return -ENOMEM;

	xfs_discard_wq = alloc_workqueue("xfsdiscard", WQ_UNBOUND, 0);
	if (!xfs_discard_wq)
		goto out_free_alloc_wq;

	return 0;
out_free_alloc_wq:
	destroy_workqueue(xfs_alloc_wq);
	return -ENOMEM;
}

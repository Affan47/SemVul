ttm_mem_global_release(struct ttm_mem_global *glob)
{
	unsigned int i;
	struct ttm_mem_zone *zone;


	ttm_page_alloc_fini();
	ttm_dma_page_alloc_fini();

	flush_workqueue(glob->swap_queue);
	destroy_workqueue(glob->swap_queue);
	glob->swap_queue = NULL;
	for (i = 0; i < glob->num_zones; ++i) {
		zone = glob->zones[i];
		kobject_del(&zone->kobj);
		kobject_put(&zone->kobj);
			}
	kobject_del(&glob->kobj);
	kobject_put(&glob->kobj);
}

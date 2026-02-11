vmw_gmrid_man_put_node(struct ttm_mem_type_manager *man,
				   struct ttm_mem_reg *mem)
{
	struct vmwgfx_gmrid_man *gman =
		(struct vmwgfx_gmrid_man *)man->priv;

	if (mem->mm_node) {
		spin_lock(&gman->lock);
		ida_remove(&gman->gmr_ida, mem->start);
		gman->used_gmr_pages -= mem->num_pages;
		spin_unlock(&gman->lock);
		mem->mm_node = NULL;
	}
}

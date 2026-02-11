dtm_cache_flush (void)
{
	unsigned int 	i;
	dtm_block_t 	*p;
	size_t entries_per_block = dtm_cache.entries_per_block;
	size_t max_blocks = dtm_cache.max_blocks;

	dtm_cache.top 				= NULL;
	dtm_cache.bot 				= NULL;
	dtm_cache.n 				= 0;

	for (i = 0; i < max_blocks; i++) {
		p = &dtm_cache.entry[i];
		p->key  	= -1;
		p->side 	= gtbNOSIDE;
		p->offset 	= gtbNOINDEX;
		p->p_arr 	= dtm_cache.buffer + i * entries_per_block;
		p->prev 	= NULL;
		p->next 	= NULL;
	}
	dtm_cache_reset_counters ();
	return;
}

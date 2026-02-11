arena_dalloc_bin_run(arena_t *arena, arena_chunk_t *chunk, arena_run_t *run,
    arena_bin_t *bin)
{
	size_t binind;
	arena_bin_info_t *bin_info;
	size_t npages, run_ind, past;

	assert(run != bin->runcur);
	assert(arena_run_tree_search(&bin->runs,
	    arena_mapp_get(chunk, ((uintptr_t)run-(uintptr_t)chunk)>>LG_PAGE))
	    == NULL);

	binind = arena_bin_index(chunk->arena, run->bin);
	bin_info = &arena_bin_info[binind];

	malloc_mutex_unlock(&bin->lock);

	npages = bin_info->run_size >> LG_PAGE;
	run_ind = (size_t)(((uintptr_t)run - (uintptr_t)chunk) >> LG_PAGE);
	past = (size_t)(PAGE_CEILING((uintptr_t)run +
	    (uintptr_t)bin_info->reg0_offset + (uintptr_t)(run->nextind *
	    bin_info->reg_interval - bin_info->redzone_size) -
	    (uintptr_t)chunk) >> LG_PAGE);
	malloc_mutex_lock(&arena->lock);


	assert(arena_mapbits_dirty_get(chunk, run_ind) ==
	    arena_mapbits_dirty_get(chunk, run_ind+npages-1));
	if (arena_mapbits_dirty_get(chunk, run_ind) == 0 && past - run_ind <
	    npages) {

		assert(npages > 0);
		arena_mapbits_large_set(chunk, run_ind, bin_info->run_size, 0);
		arena_mapbits_large_set(chunk, run_ind+npages-1, 0, 0);
		arena_run_trim_tail(arena, chunk, run, (npages << LG_PAGE),
		    ((past - run_ind) << LG_PAGE), false);

	}
	arena_run_dalloc(arena, run, true, false);
	malloc_mutex_unlock(&arena->lock);

	malloc_mutex_lock(&bin->lock);
	if (config_stats)
		bin->stats.curruns--;
}

static void free_filters(struct rar5* rar) {
	struct cdeque* d = &rar->cstate.filters;


	while(cdeque_size(d) > 0) {
		struct filter_info* f = NULL;


		if (CDE_OK == cdeque_pop_front(d, cdeque_filter_p(&f)))
			free(f);
	}

	cdeque_clear(d);


	rar->cstate.last_block_start = 0;
	rar->cstate.last_block_length = 0;
}

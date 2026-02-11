rr_select_path(struct path_selector *ps,
				      unsigned *repeat_count, size_t nr_bytes)
{
	struct selector *s = (struct selector *) ps->context;
	struct path_info *pi = NULL;

	if (!list_empty(&s->valid_paths)) {
		pi = list_entry(s->valid_paths.next, struct path_info, list);
		list_move_tail(&pi->list, &s->valid_paths);
		*repeat_count = pi->repeat_count;
	}

	return pi ? pi->path : NULL;
}

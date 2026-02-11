ql_select_path(struct path_selector *ps,
				      unsigned *repeat_count, size_t nr_bytes)
{
	struct selector *s = ps->context;
	struct path_info *pi = NULL, *best = NULL;

	if (list_empty(&s->valid_paths))
		return NULL;


	list_move_tail(s->valid_paths.next, &s->valid_paths);

	list_for_each_entry(pi, &s->valid_paths, list) {
		if (!best ||
		    (atomic_read(&pi->qlen) < atomic_read(&best->qlen)))
			best = pi;

		if (!atomic_read(&best->qlen))
			break;
	}

	if (!best)
		return NULL;

	*repeat_count = best->repeat_count;

	return best->path;
}

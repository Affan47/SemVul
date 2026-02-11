fix_unresolved_deltas(int nr_unresolved)
{
	struct delta_entry **sorted_by_pos;
	int i, n = 0;


	sorted_by_pos = xmalloc(nr_unresolved * sizeof(*sorted_by_pos));
	for (i = 0; i < nr_deltas; i++) {
		if (objects[deltas[i].obj_no].real_type != OBJ_REF_DELTA)
			continue;
		sorted_by_pos[n++] = &deltas[i];
	}
	qsort(sorted_by_pos, n, sizeof(*sorted_by_pos), delta_pos_compare);

	for (i = 0; i < n; i++) {
		struct delta_entry *d = sorted_by_pos[i];
		void *data;
		unsigned long size;
		enum object_type type;
		int j, first, last;

		if (objects[d->obj_no].real_type != OBJ_REF_DELTA)
			continue;
		data = read_sha1_file(d->base.sha1, &type, &size);
		if (!data)
			continue;

		find_delta_children(&d->base, &first, &last);
		for (j = first; j <= last; j++) {
			struct object_entry *child = objects + deltas[j].obj_no;
			if (child->real_type == OBJ_REF_DELTA)
				resolve_delta(child, data, size, type);
		}

		if (check_sha1_signature(d->base.sha1, data, size, typename(type)))
			die("local object %s is corrupt", sha1_to_hex(d->base.sha1));
		append_obj_to_pack(d->base.sha1, data, size, type);
		free(data);
		display_progress(progress, nr_resolved_deltas);
	}
	free(sorted_by_pos);
}

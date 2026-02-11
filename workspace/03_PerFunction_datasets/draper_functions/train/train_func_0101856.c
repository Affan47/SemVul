plugrack_use_by_type( plugrack_t rack,
		      const char *full_type )
{
	ListIterator it;
	plugrack_entry_t *e;

	if ( (!rack) || (!full_type) )
		return PLUGIN_INVALID_HANDLE;

	it = list_iterator_create(rack->entries);
	while ((e = list_next(it))) {
		plugin_err_t err;

		if (strcmp(full_type, e->full_type) != 0)
			continue;


		if (e->plug == PLUGIN_INVALID_HANDLE  &&
		    (err = plugin_load_from_file(&e->plug, e->fq_path)))
			error ("%s: %s", e->fq_path, plugin_strerror (err));


		if (e->plug != PLUGIN_INVALID_HANDLE)
			e->refcount++;


		list_iterator_destroy(it);
		return e->plug;
	}


	list_iterator_destroy(it);
	return PLUGIN_INVALID_HANDLE;
}

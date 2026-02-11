git_filter_list_load(
	git_filter_list **filters,
	git_repository *repo,
	git_blob *blob,
	const char *path,
	git_filter_mode_t mode,
	uint32_t options)
{
	int error = 0;
	git_filter_list *fl = NULL;
	git_filter_source src = { 0 };
	git_filter_entry *fe;
	size_t idx;
	git_filter_def *fdef;

	if (filter_registry_initialize() < 0)
		return -1;

	src.repo = repo;
	src.path = path;
	src.mode = mode;
	src.options = options;
	if (blob)
		git_oid_cpy(&src.oid, git_blob_id(blob));

	git_vector_foreach(&git__filter_registry->filters, idx, fdef) {
		const char **values = NULL;
		void *payload = NULL;

		if (!fdef || !fdef->filter)
			continue;

		if (fdef->nattrs > 0) {
			error = filter_list_check_attributes(&values, fdef, &src);
			if (error == GIT_ENOTFOUND) {
				error = 0;
				continue;
			} else if (error < 0)
				break;
		}

		if (!fdef->initialized && (error = filter_initialize(fdef)) < 0)
			break;

		if (fdef->filter->check)
			error = fdef->filter->check(
				fdef->filter, &payload, &src, values);

		git__free((void *)values);

		if (error == GIT_PASSTHROUGH)
			error = 0;
		else if (error < 0)
			break;
		else {
			if (!fl && (error = filter_list_new(&fl, &src)) < 0)
				return error;

			fe = git_array_alloc(fl->filters);
			GITERR_CHECK_ALLOC(fe);
			fe->filter  = fdef->filter;
			fe->payload = payload;
		}
	}

	if (error && fl != NULL) {
		git_array_clear(fl->filters);
		git__free(fl);
		fl = NULL;
	}

	*filters = fl;
	return error;
}

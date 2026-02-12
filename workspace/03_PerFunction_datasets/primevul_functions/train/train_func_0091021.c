static int tree_key_search(
	size_t *at_pos, git_vector *entries, const char *filename, size_t filename_len)
{
	struct tree_key_search ksearch;
	const git_tree_entry *entry;
	size_t homing, i;

	ksearch.filename = filename;
	ksearch.filename_len = filename_len;


	if (git_vector_bsearch2(&homing, entries, &homing_search_cmp, &ksearch) < 0)
		return GIT_ENOTFOUND;


	for (i = homing; i < entries->length; ++i) {
		entry = entries->contents[i];

		if (homing_search_cmp(&ksearch, entry) < 0)
			break;

		if (entry->filename_len == filename_len &&
			memcmp(filename, entry->filename, filename_len) == 0) {
			if (at_pos)
				*at_pos = i;

			return 0;
		}
	}


	if (homing > 0) {
		i = homing - 1;

		do {
			entry = entries->contents[i];

			if (homing_search_cmp(&ksearch, entry) > 0)
				break;

			if (entry->filename_len == filename_len &&
				memcmp(filename, entry->filename, filename_len) == 0) {
				if (at_pos)
					*at_pos = i;

				return 0;
			}
		} while (i-- > 0);
	}


	return GIT_ENOTFOUND;
}

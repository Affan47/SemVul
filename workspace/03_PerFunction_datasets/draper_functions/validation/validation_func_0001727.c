index_iterator__advance(
	const git_index_entry **entry, git_iterator *self)
{
	index_iterator *ii = (index_iterator *)self;
	size_t entrycount = git_vector_length(&ii->entries);
	const git_index_entry *ie;

	if (!iterator__has_been_accessed(ii))
		return index_iterator__current(entry, self);

	if (index_iterator__at_tree(ii)) {
		if (iterator__do_autoexpand(ii)) {
			ii->partial.ptr[ii->partial_pos] = ii->restore_terminator;
			index_iterator__next_prefix_tree(ii);
		} else {

			while (ii->current < entrycount) {
				ii->current++;

				if (!(ie = git_vector_get(&ii->entries, ii->current)) ||
					ii->base.prefixcomp(ie->path, ii->partial.ptr) != 0)
					break;
			}

			if (index_iterator__first_prefix_tree(ii) < 0)
				return -1;
		}
	} else {
		if (ii->current < entrycount)
			ii->current++;

		if (index_iterator__first_prefix_tree(ii) < 0)
			return -1;
	}

	return index_iterator__current(entry, self);
}

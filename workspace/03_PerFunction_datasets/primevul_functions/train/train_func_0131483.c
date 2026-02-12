enum interesting tree_entry_interesting(const struct name_entry *entry,
					struct strbuf *base, int base_offset,
					const struct pathspec *ps)
{
	enum interesting positive, negative;
	positive = do_match(entry, base, base_offset, ps, 0);


	if (!(ps->magic & PATHSPEC_EXCLUDE) ||
	    positive <= entry_not_interesting)
		return positive;

	negative = do_match(entry, base, base_offset, ps, 1);


	if (negative <= entry_not_interesting)
		return positive;


	if (S_ISDIR(entry->mode) &&
	    positive >= entry_interesting &&
	    negative == entry_interesting)
		return entry_interesting;

	if ((positive == entry_interesting &&
	     negative >= entry_interesting) ||
	    (positive == all_entries_interesting &&
	     negative == entry_interesting))
		return entry_not_interesting;

	return all_entries_not_interesting;
}

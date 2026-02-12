static int match_entry(const struct pathspec_item *item,
		       const struct name_entry *entry, int pathlen,
		       const char *match, int matchlen,
		       enum interesting *never_interesting)
{
	int m = -1;

	if (item->magic & PATHSPEC_ICASE)


		*never_interesting = entry_not_interesting;
	else if (*never_interesting != entry_not_interesting) {


		m = strncmp(match, entry->path,
			    (matchlen < pathlen) ? matchlen : pathlen);
		if (m < 0)
			return 0;


		*never_interesting = entry_not_interesting;
	}

	if (pathlen > matchlen)
		return 0;

	if (matchlen > pathlen) {
		if (match[pathlen] != '/')
			return 0;
		if (!S_ISDIR(entry->mode) && !S_ISGITLINK(entry->mode))
			return 0;
	}

	if (m == -1)


		m = ps_strncmp(item, match, entry->path, pathlen);


	if (!m)


		return 1;

	return 0;
}

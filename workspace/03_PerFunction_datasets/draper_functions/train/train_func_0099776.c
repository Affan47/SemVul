set_hpage_sizes(const char *env)
{
	char *pos;
	long size;
	char *key;
	char keys[5] = { "R\0" "W\0" "\0" };


	for (key = keys; *key != '\0'; key += 2) {
		pos = strcasestr(env, key);
		if (!pos)
			continue;

		if (*(++pos) == '=') {
			size = parse_page_size(pos + 1);
			if (size == -1)
				return size;
		} else
			size = gethugepagesize();

		if (size <= 0) {
			if (errno == ENOSYS)
				WARNING("Hugepages unavailable\n");
			else if (errno == EOVERFLOW)
				WARNING("Hugepage size too large\n");
			else
				WARNING("Hugepage size (%s)\n",
						strerror(errno));
			size = 0;
		} else if (!hugetlbfs_find_path_for_size(size)) {
			WARNING("Hugepage size %li unavailable", size);
			size = 0;
		}

		if (*key == 'R')
			hpage_readonly_size = size;
		else
			hpage_writable_size = size;
	}
	return 0;
}

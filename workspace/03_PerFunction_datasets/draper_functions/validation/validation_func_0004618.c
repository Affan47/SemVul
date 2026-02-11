register_rename_src(struct diff_filespec *one,
						   int src_path_left,
						   unsigned short score)
{
	int first, last;

	first = 0;
	last = rename_src_nr;
	while (last > first) {
		int next = (last + first) >> 1;
		struct diff_rename_src *src = &(rename_src[next]);
		int cmp = strcmp(one->path, src->one->path);
		if (!cmp)
			return src;
		if (cmp < 0) {
			last = next;
			continue;
		}
		first = next+1;
	}


	if (rename_src_alloc <= rename_src_nr) {
		rename_src_alloc = alloc_nr(rename_src_alloc);
		rename_src = xrealloc(rename_src,
				      rename_src_alloc * sizeof(*rename_src));
	}
	rename_src_nr++;
	if (first < rename_src_nr)
		memmove(rename_src + first + 1, rename_src + first,
			(rename_src_nr - first - 1) * sizeof(*rename_src));
	rename_src[first].one = one;
	rename_src[first].score = score;
	rename_src[first].src_path_left = src_path_left;
	return &(rename_src[first]);
}

should_break(struct diff_filespec *src,
			struct diff_filespec *dst,
			int break_score,
			int *merge_score_p)
{


	unsigned long delta_size, base_size, max_size;
	unsigned long src_copied, literal_added, src_removed;

	*merge_score_p = 0;


	if (S_ISREG(src->mode) != S_ISREG(dst->mode)) {
		*merge_score_p = (int)MAX_SCORE;
		return 1;
	}

	if (src->sha1_valid && dst->sha1_valid &&
	    !hashcmp(src->sha1, dst->sha1))
		return 0;

	if (diff_populate_filespec(src, 0) || diff_populate_filespec(dst, 0))
		return 0;

	base_size = ((src->size < dst->size) ? src->size : dst->size);
	max_size = ((src->size > dst->size) ? src->size : dst->size);
	if (max_size < MINIMUM_BREAK_SIZE)
		return 0;

	if (diffcore_count_changes(src, dst,
				   NULL, NULL,
				   0,
				   &src_copied, &literal_added))
		return 0;


	if (src->size < src_copied)
		src_copied = src->size;
	if (dst->size < literal_added + src_copied) {
		if (src_copied < dst->size)
			literal_added = dst->size - src_copied;
		else
			literal_added = 0;
	}
	src_removed = src->size - src_copied;


	*merge_score_p = (int)(src_removed * MAX_SCORE / src->size);
	if (*merge_score_p > break_score)
		return 1;


	delta_size = src_removed + literal_added;
	if (delta_size * MAX_SCORE / max_size < break_score)
		return 0;


	if ((src->size * break_score < src_removed * MAX_SCORE) &&
	    (literal_added * 20 < src_removed) &&
	    (literal_added * 20 < src_copied))
		return 0;

	return 1;
}

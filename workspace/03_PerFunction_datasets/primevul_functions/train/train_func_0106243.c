int diff_unmodified_pair(struct diff_filepair *p)
{


	struct diff_filespec *one = p->one, *two = p->two;

	if (DIFF_PAIR_UNMERGED(p))
		return 0;


	if (DIFF_FILE_VALID(one) != DIFF_FILE_VALID(two) ||
	    DIFF_PAIR_MODE_CHANGED(p) ||
	    strcmp(one->path, two->path))
		return 0;


	if (one->sha1_valid && two->sha1_valid &&
	    !hashcmp(one->sha1, two->sha1))
		return 1;
	if (!one->sha1_valid && !two->sha1_valid)
		return 1;
	return 0;
}

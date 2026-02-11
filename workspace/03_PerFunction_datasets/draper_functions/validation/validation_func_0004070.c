coalesce_pair(int i, int j,
	struct isl_coalesce_info *info)
{
	int same;
	enum isl_change change;

	if (harmonize_divs(&info[i], &info[j]) < 0)
		return isl_change_error;
	same = same_divs(info[i].bmap, info[j].bmap);
	if (same < 0)
		return isl_change_error;
	if (same)
		return coalesce_local_pair(i, j, info);

	if (info[i].bmap->n_div == info[j].bmap->n_div) {
		change = coalesce_local_pair(i, j, info);
		if (change != isl_change_none)
			return change;
	}

	change = check_coalesce_subset(i, j, info);
	if (change != isl_change_none)
		return change;

	return check_coalesce_eq(i, j, info);
}

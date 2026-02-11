add_wraps_around_facet(struct isl_wraps *wraps,
	struct isl_coalesce_info *info, int k, isl_int *bound,
	__isl_keep isl_set *set)
{
	struct isl_tab_undo *snap;
	int n;
	unsigned total = isl_basic_map_total_dim(info->bmap);

	snap = isl_tab_snap(info->tab);

	if (isl_tab_select_facet(info->tab, info->bmap->n_eq + k) < 0)
		return -1;
	if (isl_tab_detect_redundant(info->tab) < 0)
		return -1;

	isl_seq_neg(bound, info->bmap->ineq[k], 1 + total);

	n = wraps->mat->n_row;
	if (add_wraps(wraps, info, bound, set) < 0)
		return -1;

	if (isl_tab_rollback(info->tab, snap) < 0)
		return -1;
	if (check_wraps(wraps->mat, n, info->tab) < 0)
		return -1;

	return 0;
}

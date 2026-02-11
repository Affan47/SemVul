node_extract_partial_schedule_multi_aff(
	struct isl_sched_node *node, int first, int n)
{
	int i;
	isl_space *space;
	isl_local_space *ls;
	isl_aff *aff;
	isl_multi_aff *ma;
	int nrow;

	nrow = isl_mat_rows(node->sched);
	if (node->compressed)
		space = isl_multi_aff_get_domain_space(node->decompress);
	else
		space = isl_space_copy(node->space);
	ls = isl_local_space_from_space(isl_space_copy(space));
	space = isl_space_from_domain(space);
	space = isl_space_add_dims(space, isl_dim_out, n);
	ma = isl_multi_aff_zero(space);

	for (i = first; i < first + n; ++i) {
		aff = extract_schedule_row(isl_local_space_copy(ls), node, i);
		ma = isl_multi_aff_set_aff(ma, i - first, aff);
	}

	isl_local_space_free(ls);

	if (node->compressed)
		ma = isl_multi_aff_pullback_multi_aff(ma,
					isl_multi_aff_copy(node->compress));

	return ma;
}

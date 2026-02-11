convex_hull_pair(struct isl_basic_set *bset1,
	struct isl_basic_set *bset2)
{
	isl_basic_set *lin, *aff;
	int bounded1, bounded2;

	if (bset1->ctx->opt->convex == ISL_CONVEX_HULL_FM)
		return convex_hull_pair_elim(bset1, bset2);

	aff = isl_set_affine_hull(isl_basic_set_union(isl_basic_set_copy(bset1),
						    isl_basic_set_copy(bset2)));
	if (!aff)
		goto error;
	if (aff->n_eq != 0)
		return modulo_affine_hull(isl_basic_set_union(bset1, bset2), aff);
	isl_basic_set_free(aff);

	bounded1 = isl_basic_set_is_bounded(bset1);
	bounded2 = isl_basic_set_is_bounded(bset2);

	if (bounded1 < 0 || bounded2 < 0)
		goto error;

	if (bounded1 && bounded2)
		uset_convex_hull_wrap(isl_basic_set_union(bset1, bset2));

	if (bounded1 || bounded2)
		return convex_hull_pair_pointed(bset1, bset2);

	lin = induced_lineality_space(isl_basic_set_copy(bset1),
				      isl_basic_set_copy(bset2));
	if (!lin)
		goto error;
	if (isl_basic_set_is_universe(lin)) {
		isl_basic_set_free(bset1);
		isl_basic_set_free(bset2);
		return lin;
	}
	if (lin->n_eq < isl_basic_set_total_dim(lin)) {
		struct isl_set *set;
		set = isl_set_alloc_space(isl_basic_set_get_space(bset1), 2, 0);
		set = isl_set_add_basic_set(set, bset1);
		set = isl_set_add_basic_set(set, bset2);
		return modulo_lineality(set, lin);
	}
	isl_basic_set_free(lin);

	return convex_hull_pair_pointed(bset1, bset2);
error:
	isl_basic_set_free(bset1);
	isl_basic_set_free(bset2);
	return NULL;
}

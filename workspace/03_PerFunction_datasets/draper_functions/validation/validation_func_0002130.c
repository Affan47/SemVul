upper_bounds(
	__isl_keep isl_constraint **constraint, int n, int pos,
	__isl_keep isl_set *domain, __isl_keep isl_ast_build *build)
{
	isl_ctx *ctx;
	isl_pw_aff_list *list;
	int i;

	if (n == 0) {
		isl_pw_aff *pa;
		pa = exact_bound(domain, build, 1);
		return isl_pw_aff_list_from_pw_aff(pa);
	}

	ctx = isl_ast_build_get_ctx(build);
	list = isl_pw_aff_list_alloc(ctx,n);

	for (i = 0; i < n; ++i) {
		isl_aff *aff;

		aff = isl_constraint_get_bound(constraint[i], isl_dim_set, pos);
		aff = isl_aff_floor(aff);
		list = isl_pw_aff_list_add(list, isl_pw_aff_from_aff(aff));
	}

	return list;
}

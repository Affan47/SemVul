isl_ast_build_from_context(__isl_take isl_set *set)
{
	int i, n;
	isl_ctx *ctx;
	isl_space *space;
	isl_ast_build *build;

	set = isl_set_compute_divs(set);
	if (!set)
		return NULL;

	ctx = isl_set_get_ctx(set);

	build = isl_calloc_type(ctx, isl_ast_build);
	if (!build)
		goto error;

	build->ref = 1;
	build->domain = set;
	build->generated = isl_set_copy(build->domain);
	build->pending = isl_set_universe(isl_set_get_space(build->domain));
	build->options = isl_union_map_empty(isl_space_params_alloc(ctx, 0));
	n = isl_set_dim(set, isl_dim_set);
	build->depth = n;
	build->iterators = isl_id_list_alloc(ctx, n);
	for (i = 0; i < n; ++i) {
		isl_id *id;
		if (isl_set_has_dim_id(set, isl_dim_set, i))
			id = isl_set_get_dim_id(set, isl_dim_set, i);
		else
			id = generate_name(ctx, i, build);
		build->iterators = isl_id_list_add(build->iterators, id);
	}
	space = isl_set_get_space(set);
	if (isl_space_is_params(space))
		space = isl_space_set_from_params(space);

	return isl_ast_build_init_derived(build, space);
error:
	isl_set_free(set);
	return NULL;
}

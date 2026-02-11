create_node(__isl_take isl_union_map *executed,
	__isl_take isl_basic_set *bounds, __isl_take isl_set *domain,
	__isl_take isl_ast_build *build)
{
	struct isl_check_scaled_data data;
	isl_ctx *ctx;
	isl_aff *offset;
	isl_val *d;

	ctx = isl_ast_build_get_ctx(build);
	if (!isl_options_get_ast_build_scale_strides(ctx))
		return create_node_scaled(executed, bounds, domain, build);

	data.depth = isl_ast_build_get_depth(build);
	if (!isl_ast_build_has_stride(build, data.depth))
		return create_node_scaled(executed, bounds, domain, build);

	offset = isl_ast_build_get_offset(build, data.depth);
	data.m = isl_ast_build_get_stride(build, data.depth);
	if (!data.m)
		offset = isl_aff_free(offset);
	offset = isl_aff_scale_down_val(offset, isl_val_copy(data.m));
	d = isl_aff_get_denominator_val(offset);
	if (!d)
		executed = isl_union_map_free(executed);

	if (executed && isl_val_is_divisible_by(data.m, d))
		data.m = isl_val_div(data.m, d);
	else {
		data.m = isl_val_set_si(data.m, 1);
		isl_val_free(d);
	}

	if (!isl_val_is_one(data.m)) {
		if (isl_union_map_foreach_map(executed, &map_check_scaled,
						&data) < 0 &&
		    !isl_val_is_one(data.m))
			executed = isl_union_map_free(executed);
	}

	if (!isl_val_is_one(data.m)) {
		isl_space *space;
		isl_multi_aff *ma;
		isl_aff *aff;
		isl_map *map;
		isl_union_map *umap;

		space = isl_ast_build_get_space(build, 1);
		space = isl_space_map_from_set(space);
		ma = isl_multi_aff_identity(space);
		aff = isl_multi_aff_get_aff(ma, data.depth);
		aff = isl_aff_scale_val(aff, isl_val_copy(data.m));
		ma = isl_multi_aff_set_aff(ma, data.depth, aff);

		bounds = isl_basic_set_preimage_multi_aff(bounds,
						isl_multi_aff_copy(ma));
		domain = isl_set_preimage_multi_aff(domain,
						isl_multi_aff_copy(ma));
		map = isl_map_reverse(isl_map_from_multi_aff(ma));
		umap = isl_union_map_from_map(map);
		executed = isl_union_map_apply_domain(executed,
						isl_union_map_copy(umap));
		build = isl_ast_build_scale_down(build, isl_val_copy(data.m),
						umap);
	}
	isl_aff_free(offset);
	isl_val_free(data.m);

	return create_node_scaled(executed, bounds, domain, build);
}

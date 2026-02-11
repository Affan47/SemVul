isl_basic_map_gist(struct isl_basic_map *bmap,
	struct isl_basic_map *context)
{
	struct isl_basic_set *bset;

	if (!bmap || !context)
		goto error;

	if (isl_basic_map_is_universe(bmap)) {
		isl_basic_map_free(context);
		return bmap;
	}
	if (isl_basic_map_plain_is_empty(context)) {
		isl_basic_map_free(bmap);
		return context;
	}
	if (isl_basic_map_plain_is_empty(bmap)) {
		isl_basic_map_free(context);
		return bmap;
	}

	bmap = isl_basic_map_remove_redundancies(bmap);
	context = isl_basic_map_remove_redundancies(context);
	if (!context)
		goto error;

	if (context->n_eq)
		bmap = normalize_divs_in_context(bmap, context);

	context = isl_basic_map_align_divs(context, bmap);
	bmap = isl_basic_map_align_divs(bmap, context);

	bset = uset_gist(isl_basic_map_underlying_set(isl_basic_map_copy(bmap)),
			 isl_basic_map_underlying_set(context));

	return isl_basic_map_overlying_set(bset, bmap);
error:
	isl_basic_map_free(bmap);
	isl_basic_map_free(context);
	return NULL;
}

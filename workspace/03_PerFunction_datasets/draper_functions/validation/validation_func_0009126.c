map_gist(__isl_take isl_map *map,
	__isl_take isl_map *context)
{
	int equal;
	int is_universe;

	is_universe = isl_map_plain_is_universe(map);
	if (is_universe >= 0 && !is_universe)
		is_universe = isl_map_plain_is_universe(context);
	if (is_universe < 0)
		goto error;
	if (is_universe) {
		isl_map_free(context);
		return map;
	}

	equal = isl_map_plain_is_equal(map, context);
	if (equal < 0)
		goto error;
	if (equal) {
		isl_map *res = isl_map_universe(isl_map_get_space(map));
		isl_map_free(map);
		isl_map_free(context);
		return res;
	}

	context = isl_map_compute_divs(context);
	return isl_map_gist_basic_map(map, isl_map_simple_hull(context));
error:
	isl_map_free(map);
	isl_map_free(context);
	return NULL;
}

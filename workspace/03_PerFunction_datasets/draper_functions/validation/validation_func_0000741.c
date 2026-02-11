eliminate_divs_ineq(
		struct isl_basic_map *bmap, int *progress)
{
	int d;
	int i;
	unsigned off;
	struct isl_ctx *ctx;

	if (!bmap)
		return NULL;

	ctx = bmap->ctx;
	off = 1 + isl_space_dim(bmap->dim, isl_dim_all);

	for (d = bmap->n_div - 1; d >= 0 ; --d) {
		for (i = 0; i < bmap->n_eq; ++i)
			if (!isl_int_is_zero(bmap->eq[i][off + d]))
				break;
		if (i < bmap->n_eq)
			continue;
		for (i = 0; i < bmap->n_ineq; ++i)
			if (isl_int_abs_gt(bmap->ineq[i][off + d], ctx->one))
				break;
		if (i < bmap->n_ineq)
			continue;
		*progress = 1;
		bmap = isl_basic_map_eliminate_vars(bmap, (off-1)+d, 1);
		if (!bmap || ISL_F_ISSET(bmap, ISL_BASIC_MAP_EMPTY))
			break;
		bmap = isl_basic_map_drop_div(bmap, d);
		if (!bmap)
			break;
	}
	return bmap;
}

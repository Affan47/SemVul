isl_set_opt_aligned(__isl_keep isl_set *set, int max,
	__isl_keep isl_aff *obj, isl_int *opt)
{
	int i;
	enum isl_lp_result res;
	int empty = 1;
	isl_int opt_i;

	if (!set || !obj)
		return isl_lp_error;
	if (set->n == 0)
		return isl_lp_empty;

	res = isl_basic_set_opt(set->p[0], max, obj, opt);
	if (res == isl_lp_error || res == isl_lp_unbounded)
		return res;
	if (set->n == 1)
		return res;
	if (res == isl_lp_ok)
		empty = 0;

	isl_int_init(opt_i);
	for (i = 1; i < set->n; ++i) {
		res = isl_basic_set_opt(set->p[i], max, obj, &opt_i);
		if (res == isl_lp_error || res == isl_lp_unbounded) {
			isl_int_clear(opt_i);
			return res;
		}
		if (res == isl_lp_ok)
			empty = 0;
		if (max ? isl_int_gt(opt_i, *opt) : isl_int_lt(opt_i, *opt))
			isl_int_set(*opt, opt_i);
	}
	isl_int_clear(opt_i);

	return empty ? isl_lp_empty : isl_lp_ok;
}

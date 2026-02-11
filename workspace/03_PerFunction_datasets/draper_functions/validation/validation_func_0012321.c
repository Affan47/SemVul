gnumeric_ftest (GnmFuncEvalInfo *ei, GnmValue const * const *argv)
{
	CollectFlags flags = COLLECT_IGNORE_STRINGS | COLLECT_IGNORE_BOOLS |
		COLLECT_IGNORE_BLANKS;
	gnm_float *xs = NULL, *ys = NULL;
	int nx, ny;
	GnmValue *res = NULL;
	gnm_float p, varx, vary;

	xs = collect_floats_value (argv[0], ei->pos, flags, &nx, &res);
	if (res)
		goto out;

	ys = collect_floats_value (argv[1], ei->pos, flags, &ny, &res);
	if (res)
		goto out;

	if (gnm_range_var_est (xs, nx, &varx) ||
	    gnm_range_var_est (ys, ny, &vary) ||
	    vary == 0) {
		res = value_new_error_DIV0 (ei->pos);
		goto out;
	}

	p = pf (varx / vary, nx - 1, ny - 1, FALSE, FALSE);
	if (p > 0.5) {


		p = pf (varx / vary, nx - 1, ny - 1, TRUE, FALSE);
	}

	res = value_new_float (2 * p);

out:
	g_free (xs);
	g_free (ys);
	return res;
}

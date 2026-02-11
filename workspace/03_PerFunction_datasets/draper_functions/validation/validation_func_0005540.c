grd_D2DX2 (struct GRDMATH_INFO *info, float *stack[], GMT_LONG *constant, double *factor, GMT_LONG last)

{
	GMT_LONG i, j, k;
	double c, left, next_left;


	if (constant[last]) {
		if (gmtdefs.verbose) fprintf (stderr, "%s: Warning, operand to D2DX2 is constant!\n", GMT_program);
		memset ((void *)stack[last], 0, info->nm * sizeof (float));
		return;
	}

	for (j = k = 0; j < info->header.ny; j++) {
		c = 1.0 / (info->dx[j] * info->dx[j]);
		next_left = stack[last][k];
		stack[last][k] = (GMT_is_fnan (stack[last][k]) || GMT_is_fnan (stack[last][k+1])) ? GMT_f_NaN : (float)0.0;
		k++;
		for (i = 1; i < info->header.nx-1; i++, k++) {
			left = next_left;
			next_left = stack[last][k];
			stack[last][k] = (float)(c * (stack[last][k+1] - 2.0 * stack[last][k] + left));
		}
		stack[last][k] = (GMT_is_fnan (stack[last][k]) || GMT_is_fnan (stack[last][k-1])) ? GMT_f_NaN : (float)0.0;
		k++;
	}
}

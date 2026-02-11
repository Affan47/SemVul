ors_find_kink (double y[], GMT_LONG n, GMT_LONG mode)
{
	GMT_LONG i, ic, im;
	double *c, *f;
	double median3 (double x[]);

	if (mode == 0) {

		for (i = im = 0; i < n; i++) if (y[i] > y[im]) im = i;
		return (im);
	}


	c = (double *) GMT_memory (VNULL, n, sizeof (double), GMT_program);

	for (i = 1; i < (n-1); i++) c[i] = y[i+1] - 2.0 * y[i] + y[i-1];
	c[0] = c[1];
	if (n > 1) c[n-1] = c[n-2];


	f = (double *) GMT_memory (VNULL, n, sizeof (double), GMT_program);
	for (i = 1; i < (n-1); i++) f[i] = median3 (&c[i-1]);


	for (i = ic = 1; i < (n-1); i++) if (f[i] < f[ic]) ic = i;

	GMT_free ((void *)c);
	GMT_free ((void *)f);

	return (ic);
}

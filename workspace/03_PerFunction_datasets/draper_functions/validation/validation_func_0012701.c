GMT_quantile (double *x, double q, GMT_LONG n)
{


	GMT_LONG i_f;
	double p, f, df;

	while (n > 1 && GMT_is_dnan (x[n-1])) n--;
	if (n < 1) return (GMT_d_NaN);
	if (q == 0.0) return (x[0]);
	if (q == 100.0) return (x[n-1]);
	f = (n - 1) * q / 100.0;
	i_f = (GMT_LONG)floor (f);
	if ((df = (f - (double)i_f)) > 0.0)
		p = x[i_f+1] * df + x[i_f] * (1.0 - df);
	else
		p = x[i_f];

	return (p);
}

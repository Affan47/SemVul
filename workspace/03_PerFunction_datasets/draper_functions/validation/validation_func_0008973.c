set_bw_lambda (double cutoff, int n, double *lam1, double *lam2)
{
    int ret = 0;

    *lam1 = 1 / tan(cutoff / 2);
    *lam1 = safe_pow(*lam1, n * 2);

    fprintf(stderr, "for cutoff %g, order %d: lambda=%g, maxmod=%g\n",
	    cutoff, n, *lam1, bw_max_mod(cutoff, n));

    if (*lam1 > 1.0e18) {

	ret = 2;
    } else if (*lam1 > 1.0e6) {

	ret = 1;
    } else {

	if (*lam1 > MAX_LAM) {

	    *lam1 = sqrt(*lam1);
	    *lam2 = 1 / *lam1;
	}
    }

    return ret;
}

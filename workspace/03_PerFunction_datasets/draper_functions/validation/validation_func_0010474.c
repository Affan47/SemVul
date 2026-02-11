pnbeta2(double x, double o_x, double a, double b, double ncp,

	int lower_tail, int log_p)
{
    LDOUBLE ans = pnbeta_raw(x, o_x, a,b, ncp);


    if (lower_tail)
#ifdef HAVE_LONG_DOUBLE
	return (double) (log_p ? logl(ans) : ans);
#else
	return log_p ? log(ans) : ans;
#endif
    else {
	if (ans > 1. - 1e-10) ML_ERROR(ME_PRECISION, "pnbeta");
	if (ans > 1.0) ans = 1.0;
#if defined(HAVE_LONG_DOUBLE) && defined(HAVE_LOG1PL)
	return (double) (log_p ? log1pl(-ans) : (1. - ans));
#else

	return (double) (log_p ? log1p((double)-ans) : (1. - ans));
#endif
    }
}

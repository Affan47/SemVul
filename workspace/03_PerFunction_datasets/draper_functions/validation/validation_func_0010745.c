Binv (double p, double q)
{
    double f = NADBL;

    errno = 0;

    if (p > 0 && q > 0) {
	double x1 = ln_gamma(p + q);
	double x2 = ln_gamma(p);
	double x3 = ln_gamma(q);

	if (!na(x1) && !na(x2) && !na(x3)) {
	    f = exp(x1 - x2 - x3);
	    if (errno) {
		f = NADBL;
	    }
	}
    }

    return f;
}

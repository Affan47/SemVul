gretl_rand_normal_full (double *a, int t1, int t2,
			    double mean, double sd)
{
    int t;

    if (na(mean) && na(sd)) {
	mean = 0.0;
	sd = 1.0;
    } else if (na(mean) || na(sd) || sd <= 0.0) {
	return E_INVARG;
    }

    gretl_rand_normal(a, t1, t2);

    if (mean != 0.0 || sd != 1.0) {
	for (t=t1; t<=t2; t++) {
	    a[t] = mean + a[t] * sd;
	}
    }

    return 0;
}

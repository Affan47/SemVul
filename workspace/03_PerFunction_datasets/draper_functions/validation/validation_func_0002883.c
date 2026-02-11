ddot_(int n, double *dx, double *dy)
{
    double dtemp = 0.0;
    int i, m;

    if (n <= 0) {
	return 0;
    }

    m = n % 5;

    if (m != 0) {
	for (i = 0; i < m; ++i) {
	    dtemp += dx[i] * dy[i];
	}
	if (n < 5) {
	    return dtemp;
	}
    }

    for (i = m; i < n; i += 5) {
	dtemp = dtemp + dx[i] * dy[i] + dx[i + 1] * dy[i + 1] +
	    dx[i + 2] * dy[i + 2] + dx[i + 3] *
	    dy[i + 3] + dx[i + 4] * dy[i + 4];
    }

    return dtemp;
}

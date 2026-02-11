cull_polygon_plane(int *pn, const double *x, const double *y,
			      const struct plane *p)
{
    int n = *pn;
    int last = -1;
    int prev = n - 1;
    double x0 = x[prev];
    double y0 = y[prev];
    double d0 = dist_plane(x0, y0, p);
    int i, j;

    for (i = j = 0; i < n; i++) {
	double x1 = x[i];
	double y1 = y[i];
	double d1 = dist_plane(x1, y1, p);
	int in0 = d0 <= 0;
	int in1 = d1 <= 0;

	if (!in0 && in1 && last != prev) {
	    alloc_float(j + 1);
	    xf[j] = x0;
	    yf[j] = y0;
	    j++;
	    last = prev;
	}

	if (in1 || in0) {
	    alloc_float(j + 1);
	    xf[j] = x1;
	    yf[j] = y1;
	    j++;
	    last = i;
	}

	x0 = x1;
	y0 = y1;
	d0 = d1;
	prev = i;
    }

    *pn = j;

    return (j == 0);
}

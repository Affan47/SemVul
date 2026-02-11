shrink_clip_contours (double *x, double *y, GMT_LONG np, double w, double e, double s, double n)
{

	GMT_LONG i;

	for (i = 0; i < np; i++) {
		if (x[i] < w)
			x[i] = w;
		if (x[i] > e)
			x[i] = e;
		if (y[i] < s)
			y[i] = s;
		if (y[i] > n)
			y[i] = n;
	}
}

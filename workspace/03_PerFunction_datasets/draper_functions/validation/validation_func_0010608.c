GMT_corrcoeff_f (float *x, float *y, GMT_LONG n, GMT_LONG mode)
{


	GMT_LONG i, n_use;
	double xmean = 0.0, ymean = 0.0, dx, dy, vx, vy, vxy, r;

	if (mode == 0) {
		for (i = n_use = 0; i < n; i++) {
			if (GMT_is_fnan (x[i]) || GMT_is_fnan (y[i])) continue;
			xmean += (double)x[i];
			ymean += (double)y[i];
			n_use++;
		}
		if (n_use == 0) return (GMT_d_NaN);
		xmean /= (double)n_use;
		ymean /= (double)n_use;
	}

	vx = vy = vxy = 0.0;
	for (i = n_use = 0; i < n; i++) {
		if (GMT_is_fnan (x[i]) || GMT_is_fnan (y[i])) continue;
		dx = (double)x[i] - xmean;
		dy = (double)y[i] - ymean;
		vx += dx * dx;
		vy += dy * dy;
		vxy += dx * dy;
	}

	r = vxy / sqrt (vx * vy);
	return (r);
}

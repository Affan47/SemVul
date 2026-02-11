do_plot(
double *x,
double *y1,
double *y2,
double *y3,
int n) {
	int i, j;
	double xmin, xmax, ymin, ymax;
	double *yy[MXGPHS];

	for (j = 0; j < MXGPHS; j++)
		yy[j] = NULL;

	yy[0] = y1;
	yy[1] = y2;
	yy[2] = y3;


	xmin = ymin = 1e6;
	xmax = ymax = -1e6;

	for (i = 0; i < n; i++) {
		if (xmin > x[i])
			xmin = x[i];
		if (xmax < x[i])
			xmax = x[i];

		for (j = 0; j < MXGPHS; j++) {
			if (yy[j] != NULL) {
				if (ymin > yy[j][i])
					ymin = yy[j][i];
				if (ymax < yy[j][i])
					ymax = yy[j][i];
			}
		}
	}


	if ((xmax - xmin) == 0.0)
		xmax += 0.5, xmin -= 0.5;
	if ((ymax - ymin) == 0.0)
		ymax += 0.5, ymin -= 0.5;

	return do_plot_imp(xmin, xmax, ymin, ymax, 1.0, 1,
	                   x, NULL, yy, NULL, n,
	                   NULL, NULL, NULL, NULL, 0,
	                   NULL, NULL, NULL, NULL, NULL, 0);
}

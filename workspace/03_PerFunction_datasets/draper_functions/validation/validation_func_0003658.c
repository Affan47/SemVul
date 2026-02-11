grd_AZ_sub (struct GRDMATH_INFO *info, float *stack[], GMT_LONG *constant, double *factor, GMT_LONG last, GMT_LONG reverse)
{
	GMT_LONG i, j, prev, k;
	double x0 = 0.0, y0 = 0.0, az;
	PFD azimuth_func;

	azimuth_func = (PFD) ((GMT_IS_SPHERICAL) ? GMT_az_backaz_sphere : GMT_az_backaz_geodesic);
	prev = last - 1;
	if (constant[prev]) x0 = factor[prev];
	if (constant[last]) y0 = factor[last];
	for (k = j = i = 0; k < info->nm; k++) {
		if (!constant[prev]) x0 = (double)stack[prev][i];
		if (!constant[last]) y0 = (double)stack[last][i];
		az = (*azimuth_func) (info->grd_x[i], info->grd_y[j], x0, y0, reverse);
		while (az < -180.0) az += 360.0;
		while (az > +180.0) az -= 360.0;
		stack[prev][k] = (float)az;
		i++;
		if (i == info->header.nx) i = 0, j++;
	}
}

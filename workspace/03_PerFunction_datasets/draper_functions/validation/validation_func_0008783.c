paint_it (double x[], double y[], GMT_LONG n, double z) {
	GMT_LONG index, k;
	int rgb[3];
	struct GMT_FILL *f;

	if (n < 3) return;

	index = GMT_get_rgb_from_z (z, rgb);
	if (GMT_cpt_skip) return;


	if (project_info.three_D)
		for (k = 0; k < n; k++) GMT_xy_do_z_to_xy (x[k], y[k], project_info.z_level, &x[k], &y[k]);
	if ((index >= 0 && (f = GMT_lut[index].fill)) || (index < 0 && (f = GMT_bfn[index+3].fill))) {
		GMT_fill (x, y, (GMT_LONG)n, f, FALSE);
	}
	else
		ps_patch (x, y, (GMT_LONG)n, rgb, FALSE);
}

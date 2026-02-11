GMT_map_init_eckert4 (void) {
	double xmin, xmax, ymin, ymax, y, dummy;

	project_info.GMT_convert_latitudes = !GMT_IS_SPHERICAL;
	if (project_info.GMT_convert_latitudes) GMT_scale_eqrad ();

	if (GMT_is_dnan(project_info.pars[0])) project_info.pars[0] = 0.5 * (project_info.w + project_info.e);
	if (project_info.pars[0] < 0.0) project_info.pars[0] += 360.0;
	GMT_world_map = (fabs (fabs (project_info.e - project_info.w) - 360.0) < GMT_SMALL);
	if (project_info.units_pr_degree) project_info.pars[1] /= project_info.M_PR_DEG;
	GMT_veckert4 (project_info.pars[0]);
	project_info.x_scale = project_info.y_scale = project_info.pars[1];

	if (project_info.region) {
		y = (project_info.s * project_info.n <= 0.0) ? 0.0 : MIN (fabs(project_info.s), fabs(project_info.n));
		GMT_eckert4 (project_info.w, y, &xmin, &dummy);
		GMT_eckert4 (project_info.e, y, &xmax, &dummy);
		GMT_eckert4 (project_info.central_meridian, project_info.s, &dummy, &ymin);
		GMT_eckert4 (project_info.central_meridian, project_info.n, &dummy, &ymax);
		GMT_outside = (PFL) GMT_wesn_outside;
		GMT_crossing = (PFL) GMT_wesn_crossing;
		GMT_overlap = (PFL) GMT_wesn_overlap;
		GMT_map_clip = (PFL) GMT_wesn_clip;
		GMT_left_edge = (PFD) GMT_left_eckert4;
		GMT_right_edge = (PFD) GMT_right_eckert4;
		frame_info.horizontal = 2;
	}
	else {
		GMT_eckert4 (project_info.w, project_info.s, &xmin, &ymin);
		GMT_eckert4 (project_info.e, project_info.n, &xmax, &ymax);
		GMT_outside = (PFL) GMT_rect_outside;
		GMT_crossing = (PFL) GMT_rect_crossing;
		GMT_overlap = (PFL) GMT_rect_overlap;
		GMT_map_clip = (PFL) GMT_rect_clip;
		GMT_left_edge = (PFD) GMT_left_rect;
		GMT_right_edge = (PFD) GMT_right_rect;
		frame_info.check_side = TRUE;
	}
	GMT_map_setinfo (xmin, xmax, ymin, ymax, project_info.pars[1]);
	GMT_forward = (PFL) GMT_eckert4;
	GMT_inverse = (PFL) GMT_ieckert4;
	if (gmtdefs.basemap_type == GMT_IS_FANCY) gmtdefs.basemap_type = GMT_IS_PLAIN;
	GMT_parallel_straight = TRUE;

	return (!project_info.region);
}

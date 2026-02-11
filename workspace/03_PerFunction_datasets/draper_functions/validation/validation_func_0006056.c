calculate_set_of_isolines(
    AXIS_INDEX value_axis,
    TBOOLEAN cross,
    struct iso_curve **this_iso,
    AXIS_INDEX iso_axis,
    double iso_min, double iso_step,
    int num_iso_to_use,
    AXIS_INDEX sam_axis,
    double sam_min, double sam_step,
    int num_sam_to_use,
    TBOOLEAN need_palette)
{
    int i, j;
    struct coordinate GPHUGE *points = (*this_iso)->points;
    int do_update_color = need_palette && (!parametric || (parametric && value_axis == FIRST_Z_AXIS));

    for (j = 0; j < num_iso_to_use; j++) {
	double iso = iso_min + j * iso_step;


	(void) Gcomplex(&plot_func.dummy_values[cross ? 0 : 1],
			AXIS_DE_LOG_VALUE(iso_axis, iso), 0.0);

	for (i = 0; i < num_sam_to_use; i++) {
	    double sam = sam_min + i * sam_step;
	    struct value a;
	    double temp;

	    (void) Gcomplex(&plot_func.dummy_values[cross ? 1 : 0],
			    AXIS_DE_LOG_VALUE(sam_axis, sam), 0.0);

	    if (cross) {
		points[i].x = iso;
		points[i].y = sam;
	    } else {
		points[i].x = sam;
		points[i].y = iso;
	    }

	    evaluate_at(plot_func.at, &a);

	    if (undefined || (fabs(imag(&a)) > zero)) {
		points[i].type = UNDEFINED;
		continue;
	    }

	    temp = real(&a);
	    points[i].type = INRANGE;
	    STORE_WITH_LOG_AND_UPDATE_RANGE(points[i].z, temp, points[i].type,
					    value_axis, FALSE, NOOP, NOOP);
	    if (do_update_color) {
		COLOR_STORE_WITH_LOG_AND_UPDATE_RANGE(points[i].CRD_COLOR, temp, points[i].type,
					    COLOR_AXIS, FALSE, NOOP, NOOP);
	    }
	}
	(*this_iso)->p_count = num_sam_to_use;
	*this_iso = (*this_iso)->next;
	points = (*this_iso) ? (*this_iso)->points : NULL;
    }
}

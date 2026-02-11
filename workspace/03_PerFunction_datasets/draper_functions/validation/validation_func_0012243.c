gog_axis_base_view_point (GogView *view, double x, double y)
{
	GogAxisBase *axis_base = GOG_AXIS_BASE (view->model);
	GogAxisSet axis_set = gog_chart_get_axis_set (axis_base->chart);
	gboolean pointed = FALSE;
	GogViewAllocation const *plot_area;

	if (axis_set == GOG_AXIS_SET_UNKNOWN)
		return FALSE;


	if (GOG_IS_AXIS (view->model))
		plot_area = gog_chart_view_get_plot_area (view->parent);
	else
		plot_area = gog_chart_view_get_plot_area (view->parent->parent);

	switch (axis_set) {
		case GOG_AXIS_SET_X:
			pointed = x_process (GOG_AXIS_BASE_POINT, view, NULL, plot_area, x, y);
			break;
		case GOG_AXIS_SET_XY:
			pointed = xy_process (GOG_AXIS_BASE_POINT, view, NULL, plot_area, x, y);
			break;
		case GOG_AXIS_SET_XY_COLOR:
			if (gog_axis_get_atype (axis_base->axis) != GOG_AXIS_COLOR)
				pointed = xy_process (GOG_AXIS_BASE_POINT, view, NULL, plot_area, x, y);
			break;
		case GOG_AXIS_SET_XY_pseudo_3d:
			if (gog_axis_get_atype (axis_base->axis) != GOG_AXIS_PSEUDO_3D)
				pointed = xy_process (GOG_AXIS_BASE_POINT, view, NULL, plot_area, x, y);
			break;
		case GOG_AXIS_SET_RADAR:
			pointed = radar_process (GOG_AXIS_BASE_POINT, view, NULL, plot_area, x, y);
			break;
		case GOG_AXIS_SET_XYZ:
			xyz_process (GOG_AXIS_BASE_POINT, view, NULL, plot_area, x, y);
			break;
		default:
			g_warning ("[AxisBaseView::point] not implemented for this axis set (%i)",
				   axis_set);
			break;
	}

	return pointed;
}

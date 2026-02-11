gog_axis_set_property (GObject *obj, guint param_id,
		       GValue const *value, GParamSpec *pspec)
{
	GogAxis *axis = GOG_AXIS (obj);
	gboolean resized = FALSE;
	gboolean calc_ticks = FALSE;
	gboolean request_update = FALSE;

	switch (param_id) {
	case AXIS_PROP_TYPE:
		resized = gog_axis_set_atype (axis, g_value_get_int (value));
		break;

	case AXIS_PROP_INVERT: {
		gboolean new_inv = g_value_get_boolean (value);
		if (axis->inverted != new_inv) {
			axis->inverted = new_inv;
			resized = calc_ticks = TRUE;
		}
		break;
	}
	case AXIS_PROP_MAP: {
		const char *s = g_value_get_string (value);
		if (go_str_compare (s, axis->map_desc->name)) {
			gog_axis_map_set (axis, s);
			request_update = TRUE;
		}
		break;
	}
	case AXIS_PROP_ASSIGNED_FORMAT_STR_XL : {
		char const *str = g_value_get_string (value);
		GOFormat *newfmt = str ? go_format_new_from_XL (str) : NULL;
		resized = calc_ticks = gog_axis_set_format (axis, newfmt);
		break;
	}
	case AXIS_PROP_CIRCULAR_ROTATION:
		axis->circular_rotation = CLAMP (g_value_get_double (value),
						 GOG_AXIS_CIRCULAR_ROTATION_MIN,
						 GOG_AXIS_CIRCULAR_ROTATION_MAX);
		break;
	case AXIS_PROP_POLAR_UNIT: {
		char const *str = g_value_get_string (value);
		unsigned int i;
		for (i = 0; i < G_N_ELEMENTS (polar_units); i++) {
			if (g_ascii_strcasecmp (str, polar_units[i].name) == 0) {
				axis->polar_unit = i;
				resized = calc_ticks = TRUE;
				break;
			}
		}
		break;
	}
	case AXIS_PROP_SPAN_START:
		if (axis->type != GOG_AXIS_CIRCULAR) {
			double new_value = g_value_get_double (value);
			g_return_if_fail (new_value < axis->span_end);
			axis->span_start = new_value;
		}
		break;
	case AXIS_PROP_SPAN_END:
		if (axis->type != GOG_AXIS_CIRCULAR) {
			double new_value = g_value_get_double (value);
			g_return_if_fail (new_value > axis->span_start);
			axis->span_end = new_value;
		}
		break;
	case AXIS_PROP_COLOR_MAP: {
		char const *str = g_value_get_string (value);
		GogAxisColorMap const *map = NULL;
		if (strcmp (str, "default")) {
			GogGraph *graph = gog_object_get_graph (GOG_OBJECT (axis));
			map = gog_theme_get_color_map (gog_graph_get_theme (graph), FALSE);
			if (strcmp (gog_axis_color_map_get_id (map), str))
				map = gog_axis_color_map_get_from_id (str);
		}
		if (map) {
			axis->color_map = map;
			axis->auto_color_map = FALSE;
		}
		break;
	}

	default: G_OBJECT_WARN_INVALID_PROPERTY_ID (obj, param_id, pspec);
		 return;
	}

	if (request_update)
		gog_object_request_update (GOG_OBJECT (axis));
	else {
		if (calc_ticks)
			gog_axis_calc_ticks (axis);
		gog_object_emit_changed (GOG_OBJECT (obj), resized);
	}
}

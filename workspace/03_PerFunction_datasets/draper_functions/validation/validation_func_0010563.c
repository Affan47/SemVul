cb_polar_unit_changed (GtkComboBox *combo,
		       GogAxisPrefState *state)
{
	GogAxis *axis = state->axis;
	GOFormat *format;

	axis->polar_unit = gtk_combo_box_get_active (combo);
	format = go_format_new_from_XL (polar_units[axis->polar_unit].xl_format);

	if (gog_axis_set_format (axis, format) &&
	    state->format_selector != NULL)
		go_format_sel_set_style_format (GO_FORMAT_SEL (state->format_selector), format);
}

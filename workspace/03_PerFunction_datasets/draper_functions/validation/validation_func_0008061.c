attr_datetime (GsfXMLIn *xin, xmlChar const **attrs,
	       char const *target)
{
	unsigned y, m, d, h, mi, n;
	GnmValue *res = NULL;
	gnm_float s;

	g_return_val_if_fail (attrs != NULL, NULL);
	g_return_val_if_fail (attrs[0] != NULL, NULL);
	g_return_val_if_fail (attrs[1] != NULL, NULL);

	if (strcmp (attrs[0], target))
		return NULL;

	n = sscanf (attrs[1], "%u-%u-%uT%u:%u:%" GNM_SCANF_g,
		    &y, &m, &d, &h, &mi, &s);

	if (n >= 3) {
		GDate date;
		g_date_set_dmy (&date, d, m, y);
		if (g_date_valid (&date)) {
			XLSXReadState *state = (XLSXReadState *)xin->user_state;
			unsigned d_serial = go_date_g_to_serial (&date,
				workbook_date_conv (state->wb));
			if (n >= 6) {
				double time_frac = h + (gnm_float)mi / 60 + s / 3600;
				res = value_new_float (d_serial + time_frac / 24.);
				value_set_fmt (res, state->date_fmt);
			} else {
				res = value_new_int (d_serial);
				value_set_fmt (res, go_format_default_date ());
			}
		}
	}

	return res;
}

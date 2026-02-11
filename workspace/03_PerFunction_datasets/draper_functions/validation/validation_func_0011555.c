oo_chart_grid (GsfXMLIn *xin, xmlChar const **attrs)
{
	OOParseState *state = (OOParseState *)xin->user_state;
	gchar const *style_name = NULL;
	GogObject   *grid = NULL;

	if (state->chart.axis == NULL)
		return;
	for (; attrs != NULL && attrs[0] && attrs[1] ; attrs += 2)
		if (gsf_xml_in_namecmp (xin, CXML2C (attrs[0]), OO_NS_CHART, "class")) {
			if (attr_eq (attrs[1], "major"))
				grid = gog_object_add_by_name (state->chart.axis, "MajorGrid", NULL);
			else if (attr_eq (attrs[1], "minor"))
				grid = gog_object_add_by_name (state->chart.axis, "MinorGrid", NULL);
		} else if (gsf_xml_in_namecmp (xin, CXML2C (attrs[0]), OO_NS_CHART, "style-name"))
			style_name = CXML2C (attrs[1]);

	if (grid != NULL && style_name != NULL) {
		GOStyle *style = NULL;
		g_object_get (G_OBJECT (grid), "style", &style, NULL);

		if (style) {
			OOChartStyle *chart_style = g_hash_table_lookup
				(state->chart.graph_styles, style_name);
			if (chart_style)
				odf_apply_style_props (xin, chart_style->style_props, style);
			else
				oo_warning (xin, _("Chart style with name '%s' is missing."),
					    style_name);
			g_object_unref (style);
		}
	}
}

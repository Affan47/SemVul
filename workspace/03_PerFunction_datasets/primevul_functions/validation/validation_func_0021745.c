ms_escher_xl_to_line_type (guint16 pattern)
{
	static GOLineDashType const dash_map []= {
		GO_LINE_SOLID,
		GO_LINE_DASH,
		GO_LINE_DOT,
		GO_LINE_DASH_DOT,
		GO_LINE_DASH_DOT_DOT,
		GO_LINE_DOT,
		GO_LINE_DASH,
		GO_LINE_DASH,
		GO_LINE_DASH_DOT,
		GO_LINE_DASH_DOT,
		GO_LINE_DASH_DOT_DOT
	};

	return (pattern >= G_N_ELEMENTS (dash_map))
		? GO_LINE_SOLID
		: dash_map[pattern];
}

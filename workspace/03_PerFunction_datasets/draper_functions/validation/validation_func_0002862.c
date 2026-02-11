gnm_style_unset_element (GnmStyle *style, GnmStyleElement elem)
{
	g_return_if_fail (style != NULL);
	g_return_if_fail (MSTYLE_COLOR_BACK <= elem && elem < MSTYLE_ELEMENT_MAX);

	if (elem_is_set (style, elem)) {
		elem_clear_contents (style, elem);
		elem_unset (style, elem);
	}
}

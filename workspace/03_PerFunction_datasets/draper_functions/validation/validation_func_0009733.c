cell_draw_simplify_attributes (GnmRenderedValue *rv)
{
	PangoAttrList *pal = pango_attr_list_ref
		(pango_layout_get_attributes (rv->layout));
	gboolean recalc_height = FALSE;
	pango_attr_list_unref
		(pango_attr_list_filter
		 (pal, (PangoAttrFilterFunc) cell_draw_simplify_cb, &recalc_height));
	if (recalc_height)
		pango_layout_get_size (rv->layout, NULL,
				       &rv->layout_natural_height);
}

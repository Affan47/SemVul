go_pango_attr_list_erase (PangoAttrList *attrs, guint pos, guint len)
{
	PangoAttrList *gunk;
	struct cb_erase data;

	if (attrs == NULL)
		return;

	data.start_pos = pos;
	data.end_pos = pos + len;
	data.len = len;

	gunk = pango_attr_list_filter (attrs,
				       (PangoAttrFilterFunc)cb_delete_filter,
				       &data);
	if (gunk != NULL)
		pango_attr_list_unref (gunk);
}

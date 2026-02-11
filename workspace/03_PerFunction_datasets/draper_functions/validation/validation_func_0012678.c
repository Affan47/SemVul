go_style_sax_load_fill_image (GsfXMLIn *xin, xmlChar const **attrs)
{
	GOStyle *style = GO_STYLE (xin->user_state);
	GODoc *doc = (GODoc *) g_object_get_data (G_OBJECT (gsf_xml_in_get_input (xin)), "document");
	xmlChar const *name = NULL, *type_name = NULL;
	GType type;
	g_return_if_fail (style->fill.type == GO_STYLE_FILL_NONE);
	g_return_if_fail (GO_IS_DOC (doc));
	for (; attrs != NULL && attrs[0] && attrs[1] ; attrs += 2)
		if (0 == strcmp (attrs[0], "type"))
			style->fill.image.type = str_as_image_tiling (attrs[1]);
		else if (0 == strcmp (attrs[0], "name"))
			name = attrs[1];
		else if (0 == strcmp (attrs[0], "type-name"))
			type_name = attrs[1];
	type = type_name? g_type_from_name (type_name): GO_TYPE_PIXBUF;
	if (name && type)
		style->fill.image.image = g_object_ref (go_doc_image_fetch (doc, name, type));
	if (style->fill.image.image != NULL)
		style->fill.type = GO_STYLE_FILL_IMAGE;
}

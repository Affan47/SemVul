xlsx_run_strikethrough (GsfXMLIn *xin, xmlChar const **attrs)
{
	XLSXReadState *state = (XLSXReadState *)xin->user_state;
	for (; attrs != NULL && attrs[0] && attrs[1] ; attrs += 2)
		if (gsf_xml_in_namecmp (xin, attrs[0], XL_NS_SS, "val")) {
			PangoAttribute *attr = pango_attr_strikethrough_new (!strcmp (attrs[1], "true"));
			if (state->run_attrs == NULL)
				state->run_attrs = pango_attr_list_new ();
			pango_attr_list_insert (state->run_attrs, attr);

		}
}

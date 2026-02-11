glade_gtk_label_read_widget (GladeWidgetAdaptor *adaptor,
			     GladeWidget        *widget,
			     GladeXmlNode       *node)
{
	GladeProperty *prop;
	if (!glade_xml_node_verify
	    (node, GLADE_XML_TAG_WIDGET (glade_project_get_format (widget->project))))
		return;


        GWA_GET_CLASS (GTK_TYPE_WIDGET)->read_widget (adaptor, widget, node);

	glade_gtk_label_read_attributes (widget, node);


	prop = glade_widget_get_property (widget, "label");
	glade_gtk_label_set_label (widget->object, prop->value);


	if (!glade_widget_property_original_default (widget, "use-markup"))
		glade_widget_property_set (widget, "label-content-mode", GLADE_LABEL_MODE_MARKUP);
	else if (!glade_widget_property_original_default (widget, "pattern"))
		glade_widget_property_set (widget, "label-content-mode", GLADE_LABEL_MODE_PATTERN);
	else
		glade_widget_property_set (widget, "label-content-mode", GLADE_LABEL_MODE_ATTRIBUTES);


	if (!glade_widget_property_original_default (widget, "single-line-mode"))
		glade_widget_property_set (widget, "label-wrap-mode", GLADE_LABEL_SINGLE_LINE);
	else if (!glade_widget_property_original_default (widget, "wrap"))
		glade_widget_property_set (widget, "label-wrap-mode", GLADE_LABEL_WRAP_MODE);
	else
		glade_widget_property_set (widget, "label-wrap-mode", GLADE_LABEL_WRAP_FREE);


	if (!glade_widget_property_original_default (widget, "max-width-chars"))
		glade_widget_property_set (widget, "use-max-width", TRUE);
	else
		glade_widget_property_set (widget, "use-max-width", TRUE);

	if (glade_widget_property_original_default (widget, "use-markup"))
		glade_widget_property_set_sensitive (widget, "mnemonic-widget",
						     FALSE, MNEMONIC_INSENSITIVE_MSG);

}

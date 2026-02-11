gda_data_model_add_data_from_xml_node (GdaDataModel *model, xmlNodePtr node, GError **error)
{
	xmlNodePtr children;

	g_return_val_if_fail (GDA_IS_DATA_MODEL (model), FALSE);
	g_return_val_if_fail (node != NULL, FALSE);

	while (xmlNodeIsText (node))
		node = node->next;

	if (strcmp ((gchar*)node->name, "gda_array_data")) {
		g_set_error (error, GDA_DATA_MODEL_ERROR, GDA_DATA_MODEL_XML_FORMAT_ERROR,
			     _("Expected tag <gda_array_data>, got <%s>"), node->name);
		return FALSE;
	}

	for (children = node->xmlChildrenNode; children != NULL; children = children->next) {
		if (!strcmp ((gchar*)children->name, "gda_array_row")) {
			if (!add_xml_row (model, children, error))
				return FALSE;
		}
	}

	return TRUE;
}

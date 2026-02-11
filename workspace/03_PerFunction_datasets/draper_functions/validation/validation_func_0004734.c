empathy_plist_parse_node (xmlNode *a_node)
{
	ParseCallback parser;

	g_return_val_if_fail (a_node != NULL, NULL);
	parser = empathy_plist_get_parser_for_type (a_node->name);
	if (parser) {
		return parser (a_node);
	} else {
		return NULL;
	}
}

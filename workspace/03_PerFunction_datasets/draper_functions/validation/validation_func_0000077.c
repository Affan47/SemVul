xmldoc_parse_variablelist(struct ast_xml_node *node, const char *tabs, struct ast_str **buffer)
{
	struct ast_xml_node *tmp;
	const char *varname;
	char *vartabs;
	int ret = 0;

	if (!node || !ast_xml_node_get_children(node)) {
		return ret;
	}

	if (strcasecmp(ast_xml_node_get_name(node), "variablelist")) {
		return ret;
	}


	if (ast_asprintf(&vartabs, "%s    ", tabs) < 0) {
		return ret;
	}
	for (tmp = ast_xml_node_get_children(node); tmp; tmp = ast_xml_node_get_next(tmp)) {

		if (xmldoc_parse_common_elements(tmp, (ret ? tabs : ""), "\n", buffer)) {
			ret = 1;
			continue;
		}

		if (!strcasecmp(ast_xml_node_get_name(tmp), "variable")) {

			varname = ast_xml_get_attribute(tmp, "name");
			if (varname) {
				ast_str_append(buffer, 0, "%s<variable>%s</variable>: ", tabs, varname);
				ast_xml_free_attr(varname);

				xmldoc_parse_variable(tmp, vartabs, buffer);
				ret = 1;
			}
		}
	}

	ast_free(vartabs);

	return ret;
}

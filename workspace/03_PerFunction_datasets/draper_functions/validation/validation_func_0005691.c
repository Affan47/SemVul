xml_node_destroy(XmlNode *node)
{
	if(node->data.type == XVT_TEXT)
		g_string_free(node->data.text.value, TRUE);
	if(node->children != NULL)
		g_slist_free(node->children);
	g_free(node);
}

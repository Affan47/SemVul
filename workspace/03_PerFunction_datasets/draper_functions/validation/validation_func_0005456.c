parse_enumeration (xmlNode *node)
{
	SimpleSymbol *ret = NULL;
	xmlNode *i;
	gchar *name;

	name = (gchar*)xmlGetProp (node, (const xmlChar*)"name");
	if (!name)
		return NULL;
	ret = simple_symbol_new ();
	ret->name = name;
	ret->type = BASE_ENUM;

	for (i = node->children; i; i = i->next)
	{
		gchar *name = (gchar*)xmlGetProp (i, (const xmlChar*)"name");
		if (!name)
			continue;
		SimpleSymbol *t = simple_symbol_new ();
		t->name = name;
		ret->member = g_list_append (ret->member, t);
	}
	return IJS_SYMBOL (ret);
}

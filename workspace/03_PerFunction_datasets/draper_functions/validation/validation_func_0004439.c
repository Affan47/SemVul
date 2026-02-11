gel_makenum_string_constant (const char *str)
{
	GelETree *n;
	char *hstr;
	static GHashTable *constant_strings = NULL;

	if G_UNLIKELY (constant_strings == NULL)
		constant_strings = g_hash_table_new (g_str_hash, g_str_equal);

	hstr = g_hash_table_lookup (constant_strings, str);

	if (hstr == NULL) {
		hstr = g_strdup (str);
		g_hash_table_insert (constant_strings,
				     hstr, hstr);
	}

	GEL_GET_NEW_NODE (n);
	n->type = GEL_STRING_NODE;
	n->str.str = hstr;
	n->str.constant = TRUE;
	n->any.next = NULL;

	return n;
}

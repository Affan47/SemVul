get_indent_string (guint tabs, guint spaces)
{
	gchar *str;

	str = g_malloc (tabs + spaces + 1);
	if (tabs > 0)
		memset (str, '\t', tabs);
	if (spaces > 0)
		memset (str + tabs, ' ', spaces);
	str[tabs + spaces] = '\0';

	return str;
}

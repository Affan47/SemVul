extract_address(gchar *str)
{
	eliminate_address_comment(str);
	if (strchr_with_skip_quote(str, '"', '<'))
		extract_parenthesis_with_skip_quote(str, '"', '<', '>');
	g_strstrip(str);
}

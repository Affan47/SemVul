theme_adium_parse_body (EmpathyThemeAdium *self,
	const gchar *text,
	const gchar *token)
{
	EmpathyThemeAdiumPriv *priv = GET_PRIV (self);
	EmpathyStringParser *parsers;
	GString *string;


	parsers = empathy_webkit_get_string_parser (
		g_settings_get_boolean (priv->gsettings_chat,
			EMPATHY_PREFS_CHAT_SHOW_SMILEYS));


	string = g_string_sized_new (strlen (text));


	if (!tp_str_empty (token))
		g_string_append_printf (string,
			"<span id=\"message-token-%s\">",
			token);

	empathy_string_parser_substr (text, -1, parsers, string);

	if (!tp_str_empty (token))
		g_string_append (string, "</span>");


	g_string_prepend (string, "<div style=\"display: inline; "
					       "white-space: pre-wrap\"'>");
	g_string_append (string, "</div>");

	return g_string_free (string, FALSE);
}

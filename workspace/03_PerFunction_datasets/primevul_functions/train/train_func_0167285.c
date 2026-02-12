theme_adium_append_html (EmpathyThemeAdium *theme,
			 const gchar       *func,
			 const gchar       *html,
		         const gchar       *message,
		         const gchar       *avatar_filename,
		         const gchar       *name,
		         const gchar       *contact_id,
		         const gchar       *service_name,
		         const gchar       *message_classes,
		         gint64             timestamp,
		         gboolean           is_backlog,
		         gboolean           outgoing)
{
	EmpathyThemeAdiumPriv *priv = GET_PRIV (theme);
	GString     *string;
	const gchar *cur = NULL;
	gchar       *script;

	string = g_string_sized_new (strlen (html) + strlen (message));
	g_string_append_printf (string, "%s(\"", func);
	for (cur = html; *cur != '\0'; cur++) {
		const gchar *replace = NULL;
		gchar       *dup_replace = NULL;
		gchar       *format = NULL;

		if (theme_adium_match (&cur, "%userIconPath%")) {
			replace = avatar_filename;
		} else if (theme_adium_match (&cur, "%senderScreenName%")) {
			replace = contact_id;
		} else if (theme_adium_match (&cur, "%sender%")) {
			replace = name;
		} else if (theme_adium_match (&cur, "%senderColor%")) {

			if (outgoing) {
				replace = "inherit";
			} else if (contact_id != NULL) {
				guint hash = g_str_hash (contact_id);
				replace = colors[hash % G_N_ELEMENTS (colors)];
			}
		} else if (theme_adium_match (&cur, "%senderStatusIcon%")) {

		} else if (theme_adium_match (&cur, "%messageDirection%")) {

		} else if (theme_adium_match (&cur, "%senderDisplayName%")) {

			replace = name;
		} else if (theme_adium_match_with_format (&cur, "%textbackgroundcolor{", &format)) {

		} else if (theme_adium_match (&cur, "%message%")) {
			replace = message;
		} else if (theme_adium_match (&cur, "%time%") ||
			   theme_adium_match_with_format (&cur, "%time{", &format)) {
			const gchar *strftime_format;

			strftime_format = nsdate_to_strftime (priv->data, format);
			if (is_backlog) {
				dup_replace = empathy_time_to_string_local (timestamp,
					strftime_format ? strftime_format :
					EMPATHY_TIME_DATE_FORMAT_DISPLAY_SHORT);
			} else {
				dup_replace = empathy_time_to_string_local (timestamp,
					strftime_format ? strftime_format :
					EMPATHY_TIME_FORMAT_DISPLAY_SHORT);
			}
			replace = dup_replace;
		} else if (theme_adium_match (&cur, "%shortTime%")) {
			dup_replace = empathy_time_to_string_local (timestamp,
				EMPATHY_TIME_FORMAT_DISPLAY_SHORT);
			replace = dup_replace;
		} else if (theme_adium_match (&cur, "%service%")) {
			replace = service_name;
		} else if (theme_adium_match (&cur, "%variant%")) {

		} else if (theme_adium_match (&cur, "%userIcons%")) {

			replace = "showIcons";
		} else if (theme_adium_match (&cur, "%messageClasses%")) {
			replace = message_classes;
		} else if (theme_adium_match (&cur, "%status%")) {

		} else {
			escape_and_append_len (string, cur, 1);
			continue;
		}

		escape_and_append_len (string, replace, -1);

		g_free (dup_replace);
		g_free (format);
	}
	g_string_append (string, "\")");

	script = g_string_free (string, FALSE);
	webkit_web_view_execute_script (WEBKIT_WEB_VIEW (theme), script);
	g_free (script);
}
}
}

string_to_boolean (const gchar *str) {
	if (!g_strcmp0 (str, "true")) {
		return TRUE;
	} else if (!g_strcmp0 (str, "false")) {
		return FALSE;
	} else {
		g_error ("Unable to map '%s' into boolean", str);
	}
}

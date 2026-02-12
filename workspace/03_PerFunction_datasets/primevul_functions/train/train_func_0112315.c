static gboolean parse_cap_name(char *name, char **key, char **val)
{
	const char *eq;

	g_return_val_if_fail(name != NULL, FALSE);
	g_return_val_if_fail(name[0] != '\0', FALSE);

	eq = strchr(name, '=');

	if (eq == NULL) {
		*key = g_strdup(name);
		*val = NULL;

	} else {
		*key = g_strndup(name, (gsize)(eq - name));
		*val = g_strdup(eq + 1);
	}

	return TRUE;
}

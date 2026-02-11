expr_name_validate (const char *name)
{
	const char *p;
	GnmValue *v;

	g_return_val_if_fail (name != NULL, FALSE);

	if (name[0] == 0)
		return FALSE;

	v = value_new_from_string (VALUE_BOOLEAN, name, NULL, TRUE);
	if (!v)
		v = value_new_from_string (VALUE_BOOLEAN, name, NULL, FALSE);
	if (v) {
		value_release (v);
		return FALSE;
	}


	if (!g_unichar_isalpha (g_utf8_get_char (name)) &&
	    name[0] != '_')
		return FALSE;

	for (p = name; *p; p = g_utf8_next_char (p)) {
		if (!g_unichar_isalnum (g_utf8_get_char (p)) &&
		    p[0] != '_')
			return FALSE;
	}


	if (!expr_name_validate_a1 (name))
		return FALSE;


	if (!expr_name_validate_r1c1 (name))
		return FALSE;

	return TRUE;
}

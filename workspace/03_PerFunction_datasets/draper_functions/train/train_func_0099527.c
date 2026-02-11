totem_cmml_parse_time_str (const gchar *str)
{
	if (G_UNLIKELY (str == NULL))
		return -1.0;


	if (g_str_has_prefix (str, "npt:"))
		return totem_cmml_parse_npt (str + 4);

	if (g_str_has_prefix (str, "smpte-24:"))
		return totem_cmml_parse_smpte (str + 9, 24.0);

	if (g_str_has_prefix (str, "smpte-24-drop:"))
		return totem_cmml_parse_smpte (str + 14, 23.976);

	if (g_str_has_prefix (str, "smpte-25:"))
		return totem_cmml_parse_smpte (str + 9, 25.0);

	if (g_str_has_prefix (str, "smpte-30:"))
		return totem_cmml_parse_smpte (str + 9, 30.0);

	if (g_str_has_prefix (str, "smpte-30-drop:"))
		return totem_cmml_parse_smpte (str + 14, 29.97);

	if (g_str_has_prefix (str, "smpte-50:"))
		return totem_cmml_parse_smpte (str + 9, 50.0);

	if (g_str_has_prefix (str, "smpte-60:"))
		return totem_cmml_parse_smpte (str + 9, 60);

	if (g_str_has_prefix (str, "smpte-60-drop:"))
		return totem_cmml_parse_smpte (str + 14, 59.94);


	return totem_cmml_parse_npt (str);
}

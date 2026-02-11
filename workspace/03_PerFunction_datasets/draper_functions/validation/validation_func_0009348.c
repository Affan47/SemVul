totem_pl_parser_is_asf (const char *data, gsize len)
{
	if (len == 0)
		return NULL;

	if (g_str_has_prefix (data, "[Reference]") != FALSE
			|| g_str_has_prefix (data, "ASF ") != FALSE
			|| g_str_has_prefix (data, "[Address]") != FALSE) {
		return ASF_REF_MIME_TYPE;
	}

	return totem_pl_parser_is_asx (data, len);
}

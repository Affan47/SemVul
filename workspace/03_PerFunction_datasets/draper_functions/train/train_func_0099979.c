locale_to_utf8_normalized(const char *src, uni_norm_t norm)
{
	g_assert(src);

	return convert_to_utf8_normalized(cd_locale_to_utf8, src, norm);
}

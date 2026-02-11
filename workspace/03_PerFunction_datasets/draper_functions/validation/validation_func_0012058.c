is_dc_name(char *buf, size_t bsize, unsigned int source)
{
	static const char * const dc_int_names[] = {
		"common",
		"lcb",
		"8051",
		"lbm"
	};

	if (source < ARRAY_SIZE(dc_int_names))
		snprintf(buf, bsize, "dc_%s_int", dc_int_names[source]);
	else
		snprintf(buf, bsize, "DCInt%u", source);
	return buf;
}

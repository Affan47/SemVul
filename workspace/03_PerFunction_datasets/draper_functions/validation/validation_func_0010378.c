header_fmt_to_string(const header_fmt_t *hf)
{
	static char line[HEADER_FMT_MAX_SIZE + 1];

	header_fmt_check(hf);

	if (str_len(hf->header) >= sizeof line) {
		g_warning("trying to format too long an HTTP line (%zu bytes)",
			str_len(hf->header));
	}
	clamp_strncpy(line, sizeof line, str_2c(hf->header), str_len(hf->header));
	return line;
}

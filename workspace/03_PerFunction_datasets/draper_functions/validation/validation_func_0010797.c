mono_gc_parse_environment_string_extract_number (const char *str, size_t *out)
{
	char *endptr;
	int len = strlen (str), shift = 0;
	size_t val;
	gboolean is_suffix = FALSE;
	char suffix;

	if (!len)
		return FALSE;

	suffix = str [len - 1];

	switch (suffix) {
		case 'g':
		case 'G':
			shift += 10;
		case 'm':
		case 'M':
			shift += 10;
		case 'k':
		case 'K':
			shift += 10;
			is_suffix = TRUE;
			break;
		default:
			if (!isdigit (suffix))
				return FALSE;
			break;
	}

	errno = 0;
	val = strtol (str, &endptr, 10);

	if ((errno == ERANGE && (val == LONG_MAX || val == LONG_MIN))
			|| (errno != 0 && val == 0) || (endptr == str))
		return FALSE;

	if (is_suffix) {
		size_t unshifted;

		if (*(endptr + 1))
			return FALSE;

		unshifted = (size_t)val;
		val <<= shift;
		if (((size_t)val >> shift) != unshifted)
			return FALSE;
	}

	*out = val;
	return TRUE;
}

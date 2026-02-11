print_dirfd(const char *val)
{
	char *out;

	if (strcmp(val, "-100") == 0) {
		if (asprintf(&out, "AT_FDCWD") < 0)
			out = NULL;
	} else {
		if (asprintf(&out, "0x%s", val) < 0)
			out = NULL;
	}
	return out;
}

field_debug_raw(u_int8_t *buf, size_t len, struct constant_map **maps)
{
	char	*retval, *p;

	if (len == 0)
		return 0;
	retval = malloc(3 + len * 2);
	if (!retval)
		return 0;
	strlcpy(retval, "0x", 3 + len * 2);
	p = retval + 2;
	for (; len > 0; len--) {
		snprintf(p, 1 + len * 2, "%02x", *buf++);
		p += 2;
	}
	return retval;
}

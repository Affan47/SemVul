looks_like_urn(const char *filename)
{
	const char *p, *q;
	uint i;


	p = is_strcaseprefix(filename, "urn");

	if (p) {
	   	if ('\0' == *p++)
			return FALSE;
	} else {
		p = filename;
	}

	q = is_strcaseprefix(p, "sha1");
	if (!q)
		q = is_strcaseprefix(p, "bitprint");


	if (!q || '\0' == *q++)
		return FALSE;

	i = 0;
	while (i < SHA1_BASE32_SIZE && is_ascii_alnum(q[i]))
		i++;

	return i < SHA1_BASE32_SIZE ? FALSE : TRUE;
}

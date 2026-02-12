http_hdr_flags(const char *b, const char *e)
{
	unsigned u;
	struct http_hdrflg *retval;

	if (e == NULL)
		return (NULL);
	assert(e > b);
	u = (unsigned)(e - b);
	assert(b + u == e);
	if (u < 2 || u > 19)
		return (NULL);
	if (u > 3)
		u += http_asso_values[((const uint8_t*)b)[3]];
	if (u > 38)
		return (NULL);
	retval = &http_hdrflg[u];
	if (retval->hdr == NULL)
		return (NULL);
	if (!http_hdr_at(retval->hdr + 1, b, e - b))
		return (NULL);
	return (retval);
}

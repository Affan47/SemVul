svis(char *dst, int c, int flag, int nextc, const char *extra)
{
	char *nextra = NULL;
	visfun_t f;

	_DIAGASSERT(dst != NULL);
	_DIAGASSERT(extra != NULL);
	MAKEEXTRALIST(flag, nextra, extra);
	if (!nextra) {
		*dst = '\0';
		return dst;
	}
	f = getvisfun(flag);
	dst = (*f)(dst, c, flag, nextc, nextra);
	free(nextra);
	*dst = '\0';
	return dst;
}

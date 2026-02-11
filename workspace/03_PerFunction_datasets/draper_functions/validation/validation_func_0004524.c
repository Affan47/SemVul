istrnvisx(char *dst, size_t *dlen, const char *src, size_t len, int flag)
{
	char *extra = NULL;
	int rv;

	MAKEEXTRALIST(flag, extra, "");
	if (!extra) {
		if (dlen && *dlen == 0) {
			errno = ENOSPC;
			return -1;
		}
		*dst = '\0';
		return 0;
	}
	rv = istrsnvisx(dst, dlen, src, len, flag, extra);
	free(extra);
	return rv;
}

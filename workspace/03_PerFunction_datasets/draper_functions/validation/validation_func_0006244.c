save_string(char *dst, unsigned maxsize)
{
# if !ENABLE_UNICODE_PRESERVE_BROKEN
	ssize_t len = wcstombs(dst, command_ps, maxsize - 1);
	if (len < 0)
		len = 0;
	dst[len] = '\0';
	return len;
# else
	unsigned dstpos = 0;
	unsigned srcpos = 0;

	maxsize--;
	while (dstpos < maxsize) {
		wchar_t wc;
		int n = srcpos;


		while ((wc = command_ps[srcpos]) != BB_NUL
		    && !unicode_is_raw_byte(wc)
		) {
			srcpos++;
		}
		command_ps[srcpos] = BB_NUL;
		n = wcstombs(dst + dstpos, command_ps + n, maxsize - dstpos);
		if (n < 0)
			break;
		dstpos += n;
		if (wc == BB_NUL)
			break;


		command_ps[srcpos] = wc;
		srcpos++;
		if (dstpos == maxsize)
			break;
		dst[dstpos++] = (char) wc;
	}
	dst[dstpos] = '\0';
	return dstpos;
# endif
}

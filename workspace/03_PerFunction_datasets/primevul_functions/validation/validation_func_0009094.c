archive_wstring_append_from_mbs(struct archive_wstring *dest,
    const char *p, size_t len)
{
	size_t r;
	int ret_val = 0;


	size_t mbs_length = len;
	const char *mbs = p;
	wchar_t *wcs;
#if HAVE_MBRTOWC
	mbstate_t shift_state;

	memset(&shift_state, 0, sizeof(shift_state));
#endif


	if (NULL == archive_wstring_ensure(dest, dest->length + len + 1))
		return (-1);
	wcs = dest->s + dest->length;


	while (*mbs && mbs_length > 0) {


#if HAVE_MBRTOWC
		r = mbrtowc(wcs, mbs, mbs_length, &shift_state);
#else
		r = mbtowc(wcs, mbs, mbs_length);
#endif
		if (r == (size_t)-1 || r == (size_t)-2) {
			ret_val = -1;
			break;
		}
		if (r == 0 || r > mbs_length)
			break;
		wcs++;

		mbs += r;
		mbs_length -= r;
	}
	dest->length = wcs - dest->s;
	dest->s[dest->length] = L'\0';
	return (ret_val);
}

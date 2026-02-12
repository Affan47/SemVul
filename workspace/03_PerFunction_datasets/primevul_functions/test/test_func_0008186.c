stradd(char *d)
{
#ifdef MULTIBYTE_SUPPORT
    char *ums, *ups;
    int upslen, eol = 0;
    mbstate_t mbs;

    memset(&mbs, 0, sizeof mbs);
    ums = ztrdup(d);
    ups = unmetafy(ums, &upslen);


    while (upslen > 0) {
	wchar_t cc;
	char *pc;
	size_t cnt = eol ? MB_INVALID : mbrtowc(&cc, ups, upslen, &mbs);

	switch (cnt) {
	case MB_INCOMPLETE:
	    eol = 1;

	case MB_INVALID:

	    pc = nicechar(*ups);
	    cnt = 1;
	    memset(&mbs, 0, sizeof mbs);
	    break;
	case 0:
	    cnt = 1;

	default:

	    mb_charinit();
	    pc = wcs_nicechar(cc, NULL, NULL);
	    break;
	}

	addbufspc(strlen(pc));

	upslen -= cnt;
	ups += cnt;


	while (*pc)
	    *bv->bp++ = *pc++;
    }

    free(ums);
#else
    char *ps, *pc;
    addbufspc(niceztrlen(d));


    for (ps = d; *ps; ps++) {
	for (pc = nicechar(*ps == Meta ? *++ps^32 : *ps); *pc; pc++)
	    *bv->bp++ = *pc;
    }
#endif
}

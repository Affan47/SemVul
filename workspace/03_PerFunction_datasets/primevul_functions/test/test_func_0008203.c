prompttrunc(int arg, int truncchar, int doprint, int endchar,
	    zattr *txtchangep)
{
    if (arg > 0) {
	char ch = *bv->fm, *ptr, *truncstr;
	int truncatleft = ch == '<';
	int w = bv->bp - bv->buf;


	if (bv->truncwidth) {
	    while (*--bv->fm != '%')
		;
	    bv->fm--;
	    return 0;
	}

	bv->truncwidth = arg;
	if (*bv->fm != ']')
	    bv->fm++;
	while (*bv->fm && *bv->fm != truncchar) {
	    if (*bv->fm == '\\' && bv->fm[1])
		++bv->fm;
	    addbufspc(1);
	    *bv->bp++ = *bv->fm++;
	}
	if (!*bv->fm)
	    return 0;
	if (bv->bp - bv->buf == w && truncchar == ']') {
	    addbufspc(1);
	    *bv->bp++ = '<';
	}
	ptr = bv->buf + w;


	truncstr = ztrduppfx(ptr, bv->bp - ptr);

	bv->bp = ptr;
	w = bv->bp - bv->buf;
	bv->fm++;
	bv->trunccount = bv->dontcount;
	putpromptchar(doprint, endchar, txtchangep);
	bv->trunccount = 0;
	ptr = bv->buf + w;
	*bv->bp = '\0';


	countprompt(ptr, &w, 0, -1);
	if (w > bv->truncwidth) {


	    char *t = truncstr;
	    int fullen = bv->bp - ptr;
	    int twidth, maxwidth;
	    int ntrunc = strlen(t);

	    twidth = MB_METASTRWIDTH(t);
	    if (twidth < bv->truncwidth) {
		maxwidth = bv->truncwidth - twidth;


		addbufspc(ntrunc+1);

		ptr = bv->bp - fullen;

		if (truncatleft) {


		    char *fulltextptr, *fulltext;
		    int remw;
#ifdef MULTIBYTE_SUPPORT
		    mbstate_t mbs;
		    memset(&mbs, 0, sizeof mbs);
#endif

		    fulltextptr = fulltext = ptr + ntrunc;
		    memmove(fulltext, ptr, fullen);
		    fulltext[fullen] = '\0';


		    while (*t)
			*ptr++ = *t++;


		    remw = w;
		    while (remw > maxwidth && *fulltextptr) {
			if (*fulltextptr == Inpar) {


			    for (;;) {
				*ptr++ = *fulltextptr;
				if (*fulltextptr == '\0' ||
				    *fulltextptr++ == Outpar)
				    break;
				if (fulltextptr[-1] == Nularg)
				    remw--;
			    }
			} else {
#ifdef MULTIBYTE_SUPPORT


			    char inchar;
			    wchar_t cc;
			    int wcw;


			    if (*fulltextptr == Meta)
				inchar = *++fulltextptr ^ 32;
			    else
				inchar = *fulltextptr;
			    fulltextptr++;
			    switch (mbrtowc(&cc, &inchar, 1, &mbs)) {
			    case MB_INCOMPLETE:

				break;
			    case MB_INVALID:

				memset(&mbs, 0, sizeof mbs);

			    case 0:

				remw--;
				break;
			    default:
				wcw = WCWIDTH(cc);
				if (wcw >= 0)
				    remw -= wcw;
				else
				    remw--;
				break;
			    }
#else

			    if (*fulltextptr == Meta)
				fulltextptr++;
			    fulltextptr++;
			    remw--;
#endif
			}
		    }


		    while (*fulltextptr)
			*ptr++ = *fulltextptr++;

		    bv->bp = ptr;
		} else {


		    char *skiptext = ptr;
#ifdef MULTIBYTE_SUPPORT
		    mbstate_t mbs;
		    memset(&mbs, 0, sizeof mbs);
#endif

		    while (maxwidth > 0 && *skiptext) {
			if (*skiptext == Inpar) {

			    for (;;) {
				if (*skiptext == '\0' ||
				    *skiptext++ == Outpar)
				    break;
				if (skiptext[-1] == Nularg)
				    maxwidth--;
			    }
			} else {
#ifdef MULTIBYTE_SUPPORT
			    char inchar;
			    wchar_t cc;
			    int wcw;

			    if (*skiptext == Meta)
				inchar = *++skiptext ^ 32;
			    else
				inchar = *skiptext;
			    skiptext++;
			    switch (mbrtowc(&cc, &inchar, 1, &mbs)) {
			    case MB_INCOMPLETE:

				break;
			    case MB_INVALID:

				memset(&mbs, 0, sizeof mbs);

			    case 0:

				maxwidth--;
				break;
			    default:
				wcw = WCWIDTH(cc);
				if (wcw >= 0)
				    maxwidth -= wcw;
				else
				    maxwidth--;
				break;
			    }
#else
			    if (*skiptext == Meta)
				skiptext++;
			    skiptext++;
			    maxwidth--;
#endif
			}
		    }


		    ptr = skiptext;
		    while (*t)
			*ptr++ = *t++;
		    bv->bp = ptr;
		    if (*skiptext) {

			memmove(bv->bp, skiptext, strlen(skiptext)+1);
			skiptext = bv->bp;


			while (*skiptext) {
			    if (*skiptext == Inpar) {
				for (;;) {
				    *bv->bp++ = *skiptext;
				    if (*skiptext == Outpar ||
					*skiptext == '\0')
					break;
				    skiptext++;
				}
			    }
			    else
				skiptext++;
			}
		    }
		}
	    } else {

		while (*t)
		    *ptr++ = *t++;
		bv->bp = ptr;
	    }
	    *bv->bp = '\0';
	}
	zsfree(truncstr);
	bv->truncwidth = 0;


	if (!*bv->fm)
	    return 0;
	if (*bv->fm != endchar) {
	    bv->fm++;


	    if (!putpromptchar(doprint, endchar, txtchangep))
		return 0;
	}

	bv->fm--;
    } else {
	if (*bv->fm != endchar)
	    bv->fm++;
	while(*bv->fm && *bv->fm != truncchar) {
	    if (*bv->fm == '\\' && bv->fm[1])
		bv->fm++;
	    bv->fm++;
	}
	if (bv->truncwidth || !*bv->fm)
	    return 0;
    }
    return 1;
}

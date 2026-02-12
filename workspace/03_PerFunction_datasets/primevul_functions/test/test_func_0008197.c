countprompt(char *str, int *wp, int *hp, int overf)
{
    int w = 0, h = 1, multi = 0, wcw = 0;
    int s = 1;
#ifdef MULTIBYTE_SUPPORT
    char inchar;
    mbstate_t mbs;
    wchar_t wc;

    memset(&mbs, 0, sizeof(mbs));
#endif

    for (; *str; str++) {


	while (w > zterm_columns && overf >= 0 && !multi) {
	    h++;
	    if (wcw) {


		w = wcw;
		break;
	    } else {


		w -= zterm_columns;
	    }
	}
	wcw = 0;


	if (*str == Inpar)
	    s = 0;
	else if (*str == Outpar)
	    s = 1;
	else if (*str == Nularg)
	    w++;
	else if (s) {
	    if (*str == Meta) {
#ifdef MULTIBYTE_SUPPORT
		inchar = *++str ^ 32;
#else
		str++;
#endif
	    } else {
#ifdef MULTIBYTE_SUPPORT


		if (!multi) {
#endif
		    if (*str == '\t') {
			w = (w | 7) + 1;
			continue;
		    } else if (*str == '\n') {
			w = 0;
			h++;
			continue;
		    }
#ifdef MULTIBYTE_SUPPORT
		}

		inchar = *str;
#endif
	    }

#ifdef MULTIBYTE_SUPPORT
	    switch (mbrtowc(&wc, &inchar, 1, &mbs)) {
	    case MB_INCOMPLETE:

		multi = 1;
		break;
	    case MB_INVALID:
		memset(&mbs, 0, sizeof mbs);

		multi = 0;
		w++;
		break;
	    case 0:
		multi = 0;
		break;
	    default:


		wcw = WCWIDTH(wc);
		if (wcw >= 0)
		    w += wcw;
		else
		    w++;
		multi = 0;
		break;
	    }
#else
	    w++;
#endif
	}
    }


    while (w > zterm_columns && overf >= 0) {
	h++;
	if (wcw) {
	    w = wcw;
	    break;
	} else {
	    w -= zterm_columns;
	}
    }
    if (w == zterm_columns && overf == 0) {
	w = 0;
	h++;
    }
    if(wp)
	*wp = w;
    if(hp)
	*hp = h;
}

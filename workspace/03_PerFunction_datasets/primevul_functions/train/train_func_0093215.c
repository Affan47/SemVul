SaveText(TScreen *screen,
	 int row,
	 int scol,
	 int ecol,
	 Char *lp,
	 int *eol)
{
    LineData *ld;
    int i = 0;
    Char *result = lp;
#if OPT_WIDE_CHARS
    unsigned previous = 0;
#endif

    ld = GET_LINEDATA(screen, row);
    i = Length(screen, row, scol, ecol);
    ecol = scol + i;
#if OPT_DEC_CHRSET
    if (CSET_DOUBLE(GetLineDblCS(ld))) {
	scol = (scol + 0) / 2;
	ecol = (ecol + 1) / 2;
    }
#endif
    *eol = !LineTstWrapped(ld);
    for (i = scol; i < ecol; i++) {
	unsigned c;
	assert(i < (int) ld->lineSize);
	c = E2A(ld->charData[i]);
#if OPT_WIDE_CHARS


	if (c == HIDDEN_CHAR) {
	    if (isWide((int) previous)) {
		previous = c;


		if_OPT_WIDE_CHARS(screen, {
		    if ((screen->utf8_nrc_mode | screen->utf8_mode) != uFalse) {
			size_t off;
			for_each_combData(off, ld) {
			    unsigned ch = ld->combData[off][i];
			    if (ch == 0)
				break;
			    lp = convertToUTF8(lp, ch);
			}
		    }
		});
		continue;
	    } else {
		c = ' ';
	    }
	}
	previous = c;
	if ((screen->utf8_nrc_mode | screen->utf8_mode) != uFalse) {
	    lp = convertToUTF8(lp, (c != 0) ? c : ' ');
	    if_OPT_WIDE_CHARS(screen, {
		size_t off;
		for_each_combData(off, ld) {
		    unsigned ch = ld->combData[off][i];
		    if (ch == 0)
			break;
		    lp = convertToUTF8(lp, ch);
		}
	    });
	} else
#endif
	{
	    if (c == 0) {
		c = E2A(' ');
	    } else if (c < E2A(' ')) {
		c = DECtoASCII(c);
	    } else if (c == 0x7f) {
		c = 0x5f;
	    }
	    *lp++ = CharOf(A2E(c));
	}
	if (c != E2A(' '))
	    result = lp;
    }


    if (!*eol || !screen->trim_selection)
	result = lp;

    return (result);
}

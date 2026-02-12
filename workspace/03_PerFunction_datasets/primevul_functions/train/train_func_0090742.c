escapes(cp, tp)
const char	*cp;
char *tp;
{
    static NEARDATA const char
	oct[] = "01234567", dec[] = "0123456789",
	hex[] = "00112233445566778899aAbBcCdDeEfF";
    const char *dp;
    int cval, meta, dcount;

    while (*cp) {


	meta = (*cp == '\\' && (cp[1] == 'm' || cp[1] == 'M') && cp[2]);
	if (meta) cp += 2;

	cval = dcount = 0;
	if ((*cp != '\\' && *cp != '^') || !cp[1]) {

	    cval = *cp++;
	} else if (*cp == '^') {
	    cval = (*++cp & 0x1f);
	    ++cp;

	} else if (index(dec, cp[1])) {
	    ++cp;
	    do {
		cval = (cval * 10) + (*cp - '0');
	    } while (*++cp && index(dec, *cp) && ++dcount < 3);
	} else if ((cp[1] == 'o' || cp[1] == 'O') &&
		cp[2] && index(oct, cp[2])) {
	    cp += 2;
	    do {
		cval = (cval * 8) + (*cp - '0');
	    } while (*++cp && index(oct, *cp) && ++dcount < 3);
	} else if ((cp[1] == 'x' || cp[1] == 'X') &&
		cp[2] && (dp = index(hex, cp[2])) != 0) {
	    cp += 2;
	    do {
		cval = (cval * 16) + ((int)(dp - hex) / 2);
	    } while (*++cp && (dp = index(hex, *cp)) != 0 && ++dcount < 2);
	} else {
	    switch (*++cp) {
	    case '\\': cval = '\\'; break;
	    case 'n': cval = '\n'; break;
	    case 't': cval = '\t'; break;
	    case 'b': cval = '\b'; break;
	    case 'r': cval = '\r'; break;
	    default: cval = *cp;
	    }
	    ++cp;
	}

	if (meta)
	    cval |= 0x80;
	*tp++ = (char)cval;
    }
    *tp = '\0';
}

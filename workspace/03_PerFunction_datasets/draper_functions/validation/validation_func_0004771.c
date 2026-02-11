addtype(const zic_t gmtoff, const char *const abbr, const int isdst,
	const int ttisstd, const int ttisgmt)
{
	register int	i, j;

	if (isdst != TRUE && isdst != FALSE) {
		error(_("internal error - addtype called with bad isdst"));
		exit(EXIT_FAILURE);
	}
	if (ttisstd != TRUE && ttisstd != FALSE) {
		error(_("internal error - addtype called with bad ttisstd"));
		exit(EXIT_FAILURE);
	}
	if (ttisgmt != TRUE && ttisgmt != FALSE) {
		error(_("internal error - addtype called with bad ttisgmt"));
		exit(EXIT_FAILURE);
	}


	for (i = 0; i < typecnt; ++i) {
		if (gmtoff == gmtoffs[i] && isdst == isdsts[i] &&
			strcmp(abbr, &chars[abbrinds[i]]) == 0 &&
			ttisstd == ttisstds[i] &&
			ttisgmt == ttisgmts[i])
				return i;
	}


	if (typecnt >= TZ_MAX_TYPES) {
		error(_("too many local time types"));
		exit(EXIT_FAILURE);
	}
	if (! (-1L - 2147483647L <= gmtoff && gmtoff <= 2147483647L)) {
		error(_("UT offset out of range"));
		exit(EXIT_FAILURE);
	}
	gmtoffs[i] = gmtoff;
	isdsts[i] = isdst;
	ttisstds[i] = ttisstd;
	ttisgmts[i] = ttisgmt;

	for (j = 0; j < charcnt; ++j)
		if (strcmp(&chars[j], abbr) == 0)
			break;
	if (j == charcnt)
		newabbr(abbr);
	abbrinds[i] = j;
	++typecnt;
	return i;
}

PGLC_localeconv(void)
{
	static struct lconv CurrentLocaleConv;
	struct lconv *extlconv;
	char	   *save_lc_monetary;
	char	   *save_lc_numeric;
	char	   *decimal_point;
	char	   *grouping;
	char	   *thousands_sep;
	int			encoding;

#ifdef WIN32
	char	   *save_lc_ctype;
#endif


	if (CurrentLocaleConvValid)
		return &CurrentLocaleConv;

	free_struct_lconv(&CurrentLocaleConv);


	save_lc_monetary = setlocale(LC_MONETARY, NULL);
	if (save_lc_monetary)
		save_lc_monetary = pstrdup(save_lc_monetary);

	save_lc_numeric = setlocale(LC_NUMERIC, NULL);
	if (save_lc_numeric)
		save_lc_numeric = pstrdup(save_lc_numeric);

#ifdef WIN32


	save_lc_ctype = setlocale(LC_CTYPE, NULL);
	if (save_lc_ctype)
		save_lc_ctype = pstrdup(save_lc_ctype);


	setlocale(LC_CTYPE, locale_numeric);
#endif


	setlocale(LC_NUMERIC, locale_numeric);
	extlconv = localeconv();
	encoding = pg_get_encoding_from_locale(locale_numeric);

	decimal_point = db_encoding_strdup(encoding, extlconv->decimal_point);
	thousands_sep = db_encoding_strdup(encoding, extlconv->thousands_sep);
	grouping = strdup(extlconv->grouping);

#ifdef WIN32

	setlocale(LC_CTYPE, locale_monetary);
#endif


	setlocale(LC_MONETARY, locale_monetary);
	extlconv = localeconv();
	encoding = pg_get_encoding_from_locale(locale_monetary);


	CurrentLocaleConv = *extlconv;
	CurrentLocaleConv.decimal_point = decimal_point;
	CurrentLocaleConv.grouping = grouping;
	CurrentLocaleConv.thousands_sep = thousands_sep;
	CurrentLocaleConv.int_curr_symbol = db_encoding_strdup(encoding, extlconv->int_curr_symbol);
	CurrentLocaleConv.currency_symbol = db_encoding_strdup(encoding, extlconv->currency_symbol);
	CurrentLocaleConv.mon_decimal_point = db_encoding_strdup(encoding, extlconv->mon_decimal_point);
	CurrentLocaleConv.mon_grouping = strdup(extlconv->mon_grouping);
	CurrentLocaleConv.mon_thousands_sep = db_encoding_strdup(encoding, extlconv->mon_thousands_sep);
	CurrentLocaleConv.negative_sign = db_encoding_strdup(encoding, extlconv->negative_sign);
	CurrentLocaleConv.positive_sign = db_encoding_strdup(encoding, extlconv->positive_sign);


	if (save_lc_monetary)
	{
		setlocale(LC_MONETARY, save_lc_monetary);
		pfree(save_lc_monetary);
	}

	if (save_lc_numeric)
	{
		setlocale(LC_NUMERIC, save_lc_numeric);
		pfree(save_lc_numeric);
	}

#ifdef WIN32

	if (save_lc_ctype)
	{
		setlocale(LC_CTYPE, save_lc_ctype);
		pfree(save_lc_ctype);
	}
#endif

	CurrentLocaleConvValid = true;
	return &CurrentLocaleConv;
}

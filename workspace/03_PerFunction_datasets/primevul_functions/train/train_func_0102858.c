fmtfloat(double value, char type, int forcesign, int leftjust,
		 int minlen, int zpad, int precision, int pointflag,
		 PrintfTarget *target)
{
	int			signvalue = 0;
	int			prec;
	int			vallen;
	char		fmt[32];
	char		convert[1024];
	int			zeropadlen = 0;
	int			padlen = 0;


	if (precision < 0)
		precision = 0;
	prec = Min(precision, 350);

	if (pointflag)
	{
		sprintf(fmt, "%%.%d%c", prec, type);
		zeropadlen = precision - prec;
	}
	else
		sprintf(fmt, "%%%c", type);

	if (!isnan(value) && adjust_sign((value < 0), forcesign, &signvalue))
		value = -value;

	vallen = sprintf(convert, fmt, value);


	if (zeropadlen > 0 && !isdigit((unsigned char) convert[vallen - 1]))
		zeropadlen = 0;

	adjust_padlen(minlen, vallen + zeropadlen, leftjust, &padlen);

	leading_pad(zpad, &signvalue, &padlen, target);

	if (zeropadlen > 0)
	{

		char	   *epos = strrchr(convert, 'e');

		if (!epos)
			epos = strrchr(convert, 'E');
		if (epos)
		{

			dostr(convert, epos - convert, target);
			while (zeropadlen-- > 0)
				dopr_outch('0', target);
			dostr(epos, vallen - (epos - convert), target);
		}
		else
		{

			dostr(convert, vallen, target);
			while (zeropadlen-- > 0)
				dopr_outch('0', target);
		}
	}
	else
	{

		dostr(convert, vallen, target);
	}

	trailing_pad(&padlen, target);
}
